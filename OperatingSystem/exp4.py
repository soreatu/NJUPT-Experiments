HELP = """\
==========HELP==========
$ mkfile <filename> <content>     make a new file
$ dir                             list all the files
$ type   <filename>               show the content of a file
$ del    <filename>               delete a file
$ quit                            exit the program
==========HELP==========
"""

PROMT = "$ "


class FileSystem():
    def __init__(self):
        self._disk = [[0 for _ in range(16)] for _ in range(16)]   # 硬盘容量：1024-byte（16个16-byte的块）
        self._fat = self._disk[0]
        for i in range(1, 5):
            self._disk[i][0] = 0xE5        # 4个目录项均空闲
        for j in range(5):
            self._fat[j] = 0xFF  # 前5块均被占用


    def _mkfile(self, filename, content):
        # 是否有空闲目录项？
        free_fcb = None
        for i in range(1, 5):
            if self._disk[i][0] == 0xE5:  # 有空闲的目录项
                free_fcb = i
                # print(f"free_fcb: {free_fcb}")
                break
        if free_fcb == None:
            print("No more free FCB!")
            return False

        # 是否有足够多的块？
        filesize = len(content)
        fileBlockNum = (filesize-1)//16 + 1
        # print(f"fileBlockNum: {fileBlockNum}")
        if sum(block==0x00 for block in self._fat) < fileBlockNum:
            print("Not enough blocks to store the file!")
            return False

        lastBlock = None
        for i in range(fileBlockNum):
            # 找到一个空闲块
            block = self._fat.index(0x00)
            # print(f"i: {i}, block: {block}")
            # 将文件内容写入这个块中
            self._disk[block] = list(content[i*16:(i+1)*16].ljust(16, b"\x00"))
            self._fat[block] = 0xFF
            # 如果是首块，则将其写入FCB中
            if i == 0:
                data = filename.ljust(8, b"\x00")           # 8-byte文件名
                data += int.to_bytes(filesize, 4, "little")    # 4-byte的文件大小
                data += int.to_bytes(block, 4, "little")       # 4-byte的初始块号
                # print(data)
                self._disk[free_fcb] = list(data)
            if lastBlock:
                self._fat[lastBlock] = block
            lastBlock = block

        # print(self._disk)
        return True

    def _dir(self):
        print(f"{'filename':8s}   filesize")
        print("----------------------------")
        for i in range(1, 5):
            fcb = self._disk[i]
            if fcb[0] != 0xE5:
                filename = bytes(fcb[:8]).strip(b"\x00").decode("utf-8")
                filesize = int.from_bytes(fcb[8:12], "little")
                print(f"{filename:8s}  {filesize:4d} bytes")

    def _type(self, name):
        for i in range(1, 5):
            fcb = self._disk[i]
            if fcb[0] != 0xE5:
                filename = bytes(fcb[:8]).strip(b"\x00").decode("utf-8")
                blockNum = int.from_bytes(fcb[12:16], "little")
                if filename == name:
                    content = b""
                    while blockNum != 0xFF:
                        content += bytes(self._disk[blockNum])
                        blockNum = self._fat[blockNum]
                    print(content.decode("utf-8"))
                    return
        print(f"No such file: {name}")

    def _del(self, name):
        for i in range(1, 5):
            fcb = self._disk[i]
            if fcb[0] != 0xE5:
                filename = bytes(fcb[:8]).strip(b"\x00").decode("utf-8")
                blockNum = int.from_bytes(fcb[12:16], "little")
                if filename == name:
                    # fcb
                    fcb[0] = 0xE5
                    # fat
                    while blockNum != 0xFF:
                        nextBlock = self._fat[blockNum]
                        self._fat[blockNum] = 0x00
                        blockNum = nextBlock
                    # print(self._disk)
                    return
        print(f"No such file: {name}")

    # handlers
    def mkfile_handler(self, filename, content):
        filename, content = filename.encode("utf-8"), content.encode("utf-8")
        if len(filename) > 8:
            print(f"Filename is too long: {len(filename)}!")
            return
        if self._mkfile(filename, content):
            print("Success!")
        else:
            print("Error!")

    def dir_handler(self):
        self._dir()

    def type_handler(self, filename):
        self._type(filename)

    def del_handler(self, filename):
        self._del(filename)


def main():
    fs = FileSystem()
    print(HELP)
    while True:
        try:
            inp = input(PROMT)
            command = inp.split(" ")
            if command[0] == "mkfile":
                fs.mkfile_handler(command[1], command[2])
            elif command[0] == "dir":
                fs.dir_handler()
            elif command[0] == "type":
                fs.type_handler(command[1])
            elif command[0] == "del":
                fs.del_handler(command[1])
            elif command[0] == "help":
                print(HELP)
            elif command[0] == "quit":
                print("Bye!")
                return 0
            else:
                print(f"Unknown command: {inp}")
                print(HELP)
        except IndexError as e:
            print(f"Wrong format of command: {inp}")
            print(HELP)
            continue


if __name__ == "__main__":
    main()
#-*- coding: utf-8 -*-

def getLogger():
    import logging
    import sys
    logger = logging.getLogger()
    formatter = logging.Formatter("%(asctime)s\t%(levelname)s\t%(message)s")

    fileHandler = logging.FileHandler("debug.log", encoding='utf-8')
    fileHandler.setFormatter(formatter)
    logger.addHandler(fileHandler)
    """
    streamHandler = logging.StreamHandler(sys.stdout)
    streamHandler.setFormatter(formatter)
    logger.addHandler(streamHandler)
    """

    logger.setLevel(logging.NOTSET)
    return logger

if __name__ == "__main__":
    logger = getLogger()
    logger.info("test")
    raw_input()
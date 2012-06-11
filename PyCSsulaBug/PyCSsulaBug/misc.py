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

def comicInfoToString(comicInfo):
    string = u"comicInfo{{coverUrl='{}', key='{}', name='{}', author='{}', type='{}', lastUpdated='{}', description='{}'}}"
    return string.format(comicInfo.get('coverUrl', u'not set'),
                         comicInfo.get('key', u'not set'),
                         comicInfo.get('name', u'not set'),
                         comicInfo.get('author', u'not set'),
                         comicInfo.get('type', u'not set'),
                         comicInfo.get('lastUpdated', u'not set'),
                         comicInfo.get('description', u'not set'))


if __name__ == "__main__":
    logger = getLogger()
    logger.info(u"test")
    raw_input()
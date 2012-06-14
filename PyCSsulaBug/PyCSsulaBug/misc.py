#-*- coding: utf-8 -*-

import logging


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
    raw_input()
#-*- config: utf-8 -*-

import logging

logging.basicConfig(
                    filename="Debug.log",
                    format="%(levelname)s:%(funcName)s:%(message)s",
                    level=logging.NOTSET
)
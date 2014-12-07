#!/usr/bin/python
# ----------------------------------------------------------------------------
# cocos "install" plugin
#
# Authr: Luis Parravicini
#
# License: MIT
# ----------------------------------------------------------------------------
'''
"xxhash" plugin for cocos command line tool
'''

__docformat__ = 'restructuredtext'

import sys
import os
import cocos
import BaseHTTPServer
import webbrowser
import threading


class CCPluginHash(cocos.CCPlugin):
    """
    xxhash the proj.android/bin/classes.dex file
    """

    @staticmethod
    def depends_on():
        return ('compile',)

    @staticmethod
    def plugin_name():
      return "xxhash"

    @staticmethod
    def brief_description():
        return "xxhash the android classes.dex file"

    def _add_custom_options(self, parser):
        parser.add_argument("-m", "--mode", dest="mode", default='debug',
                          help="Set the run mode, should be debug|release, default is debug.")

        #group = parser.add_argument_group("web project arguments")
        #group.add_argument("port", metavar="SERVER_PORT", nargs='?', default='8000',
        #                  help="Set the port of the local web server, defualt is 8000")

    def _check_custom_options(self, args):
        #self._port = args.port
        self._mode = args.mode

    def xxhash_android_classes(self, args):
        project_dir = self._project.get_project_dir()
        hash_path = os.path.join(os.path.dirname(__file__), 'bin', 'hash')

        xxhashclasses = '%s -f %s -t %s' % (hash_path, project_dir + '/proj.android/bin/classes.dex', project_dir + '/Resources/config.et')
        cocos.Logging.debug('[xxhash android classes] : ' + xxhashclasses)

        self._run_cmd(xxhashclasses)


    def run(self, argv, dependencies):
        self.parse_args(argv)
        cocos.Logging.info('Building mode: %s' % self._mode)
        self.xxhash_android_classes(argv)
        


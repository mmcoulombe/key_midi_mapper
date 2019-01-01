#! /usr/bin/env python
# encoding: utf-8

from waflib.Tools.compiler_cxx import cxx_compiler
cxx_compiler['win32'] = ['g++']

VERSION='0.0.1'
APPNAME='midi_mapper'

top = '.'
out = 'build'

def options(opt):
  opt.load('compiler_cxx')
  opt.add_option('--mode', action='store', dest='MODE',
    default='debug', help='debug or release'
  )

def configure(conf):
  conf.load('compiler_cxx')
  conf.check(header_name='stdio.h', features='cxx cxxprogram', mandatory=False)

  # compiler flags
  conf.env.CXXFLAGS = ['-std=c++17', '-pipe', '-Wall']

  if conf.options.MODE == 'debug':
    print('Building in debug mode')
    conf.env.CXXFLAGS += ['-g']
  
def build(bld):
  cppSrc = bld.path.ant_glob('src/**/*.cpp')
  bld.program(
    source=cppSrc + ['main.cpp'],
    target='midi_mapper',

    includes = ['./include', 'C:/CppLibs/tl/include', 'C:/CppLibs/cpptoml/include'],

    lib = ["Winmm"],
    # libpath = [''],
    install_path = None
  )
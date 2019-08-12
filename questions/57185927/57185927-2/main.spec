# -*- mode: python ; coding: utf-8 -*-

# https://stackoverflow.com/a/50402636/6622587
import os
spec_root = os.path.abspath(SPECPATH)

block_cipher = None


a = Analysis(['main.py'],
             pathex=[spec_root],
             binaries=[],
             datas=[],
             hiddenimports=['PySide2.QtXml', 'packaging.specifiers', 'packaging.requirements'],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          [],
          exclude_binaries=True,
          name='main',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          console=True )
coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas,
               strip=False,
               upx=True,
               upx_exclude=[],
               name='main')

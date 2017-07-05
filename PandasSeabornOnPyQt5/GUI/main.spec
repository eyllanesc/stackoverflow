# -*- mode: python -*-

block_cipher = None


a = Analysis(['main.py'],
             pathex=['/home/qhipa/PandasSeabornOnPyQt5/GUI'],
             binaries=[],
             datas=[],
             hiddenimports=['appdirs', 'packaging', 'packaging.version', 'packaging.specifiers', 'packaging.requirements', 'sklearn.neighbors.typedefs'],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          name='main',
          debug=False,
          strip=False,
          upx=True,
          console=False )

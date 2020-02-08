import os
cfiles = []
for root, dirs, files in os.walk('C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Enterprise\\'):
  for file in files:
    if file.find('nclude')>=0:
      print(os.path.join(root, file))

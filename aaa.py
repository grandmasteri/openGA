import os
cfiles = []
# for root, dirs, files in os.walk('C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Enterprise\\'):
for root, dirs, files in os.walk('C:\\Program Files (x86)\\Microsoft Visual Studio\\'):
  for file in files:
    if file.startswith('uuid.lib'):
      print(os.path.join(root, file))

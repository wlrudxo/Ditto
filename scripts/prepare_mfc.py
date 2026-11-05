import json, pathlib, urllib.request, zipfile, hashlib, concurrent.futures
root=pathlib.Path(__file__).resolve().parents[1]/'local'
root.mkdir(exist_ok=True)
payloads=json.loads(pathlib.Path(__file__).with_name('mfc-packages.json').read_text())
def get(p):
 f=root/p['fileName'];urllib.request.urlretrieve(p['url'],f)
 assert hashlib.sha256(f.read_bytes()).hexdigest().lower()==p['sha256'].lower(), f
 return f
files=list(concurrent.futures.ThreadPoolExecutor(4).map(get,payloads))
for f in files:
 with zipfile.ZipFile(f) as z:
  for n in z.namelist():
   if '/atlmfc/' in n.lower() and not n.endswith('/'):
    rel=n[n.lower().index('/atlmfc/')+1:];out=root/'msvc'/rel
    out.parent.mkdir(parents=True,exist_ok=True);out.write_bytes(z.read(n))
print('Verified and extracted',len(files),'Microsoft packages; headers',list((root/'msvc'/'atlmfc'/'include').glob('afxwin.h')))
(root/'mfc-packages.json').write_text(json.dumps(payloads,indent=2))

props = """<Project xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
<PropertyGroup><CheckMSVCComponents>false</CheckMSVCComponents></PropertyGroup>
<ItemDefinitionGroup>
<ClCompile><AdditionalIncludeDirectories>$(MSBuildThisFileDirectory)msvc\\atlmfc\\include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories></ClCompile>
<ResourceCompile><AdditionalIncludeDirectories>$(MSBuildThisFileDirectory)msvc\\atlmfc\\include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories></ResourceCompile>
<Link><AdditionalLibraryDirectories>$(MSBuildThisFileDirectory)msvc\\atlmfc\\lib\\x64;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories></Link>
</ItemDefinitionGroup></Project>"""
(root/'mfc.props').write_text(props, encoding='utf-8')

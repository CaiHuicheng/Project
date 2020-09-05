
Tanks warps.dll: dlldata.obj Tanks war_p.obj Tanks war_i.obj
	link /dll /out:Tanks warps.dll /def:Tanks warps.def /entry:DllMain dlldata.obj Tanks war_p.obj Tanks war_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Tanks warps.dll
	@del Tanks warps.lib
	@del Tanks warps.exp
	@del dlldata.obj
	@del Tanks war_p.obj
	@del Tanks war_i.obj

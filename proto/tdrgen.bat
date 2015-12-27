::���������Ŀ�ĸ�������TDR��XML�����ļ�������H,CPP�ļ���(�����Ŷ��ڲ��Ĺ淶)
::ͬʱΪ�˱����ظ����ɣ���ɴ�Ҷ�α��룬ʹ�����ļ��򵥵��ļ�ʱ����ȽϹ���
::���ú�Э�鲿�ֵַ�ʹ�ò�ͬ�ķ�ʽ����ΪTDR���Լ��Ĳ�������ر���ĿǰC���԰汾(���в�ͬƽ̨�����ݵ�����)��������Ժ󻻵�C++�汾Ҳ���һ��,

::bat�Ǹ�������Ķ������Ҹ��˾���������Ϊ����Ա׼���ģ�ϣ����ϲ����
::http://www.bathome.net/ ����������ĸ������ϣ�������������վ�ҵ����Ƚ�ȫ����
::BTW�����ڸ�����cmd��ʱ�����֧��s�����������һ�����ڱ��룬����Ȼ���ܱ�������

::�����ʽ˵��tdrgen ����1�������Ŀ¼  [����2����ص�ƽ̨,win32,x64]��
::����2��ѡ������������������㵱ǰ�Ļ������о���,

@echo off

setlocal 

::--------------------------------------------------------------------------------------------

set cur_path_=%~dp0
set os_name_=%~1

if "%os_name_%"=="" (
    if /i "%PROCESSOR_IDENTIFIER:~0,3%"=="x86" ( set os_name_=win32) else ( set os_name_=win64)
)else (
    if /i "%os_name_%"=="win32" ( set os_name_=win32) else ( set os_name_=win64)
)

::ʵ�ּ򵥵��ļ�ʱ����ȽϹ��ܣ�

set xml_filename_=
set xml_timestamp_=
set h_filename_=
set h_timestamp_=
set cpp_filename_=
set cpp_timestamp_=
set game_channel_file_name=

::�����Ŀ¼����������ӣ����ں�������
set process_set_=.\

:: bat�б����ۼ���Ҫʹ��!,����Ҫ���ӳ���չ
:: �����ӳ���չ�����Ķ�http://www.bathome.net/thread-2189-1-1.html
setlocal enabledelayedexpansion

for %%d in (%process_set_%) do (
    set process_dir_=%%d
    echo Check dir [!cur_path_!!process_dir_!]

    for /f "delims==" %%i in ('dir /b !process_dir_!*_proto*.xml ' ) do (
        set xml_filename_=!process_dir_!%%i
        set cpp_filename_=!xml_filename_:~0,-3!cpp
        set h_filename_=!xml_filename_:~0,-3!h

        ::����ļ������ڣ�֮��������Ҫ����м��
        if not exist !cpp_filename_! ( goto label_need_tdr )
        if not exist !h_filename_! ( goto label_need_tdr )
        
        for /f "delims==" %%x in ("!xml_filename_!") do (
           ::echo %%x %%~tx
           set xml_timestamp_=%%~tx
           set xml_timestamp_=!xml_timestamp_: =!
        )

        ::�Ƚ�CPP�ļ���ʱ�����XML�ļ���ʱ���
        for /f "delims==" %%x in ("!cpp_filename_!") do (
           ::echo %%x %%~tx
           set cpp_timestamp_=%%~tx
           set cpp_timestamp_=!cpp_timestamp_: =!
           if !cpp_timestamp_! leq !xml_timestamp_! ( goto label_need_tdr )
        )
        
        ::�Ƚ�H�ļ���ʱ�����XML�ļ���ʱ���
        for /f "delims==" %%y in ("!h_filename_!") do (
           ::echo %%y %%~ty
           set h_timestamp_=%%~ty
           set h_timestamp_=!h_timestamp_: =!
           if !h_timestamp_! leq !xml_timestamp_! ( goto label_need_tdr )
        )
    )
)

:label_notneed_tdr
echo not need tdr process
goto label_right_exit

:label_need_tdr
echo need tdr process
::--------------------------------------------------------------------------------------------

::ѡ��TDR����


set tdr_cmd_=%~dp0\tdr.exe

:: for�м���set�������ӳ���չ,
setlocal enabledelayedexpansion

for %%d in (%process_set_%) do (
    :: ����Э��TDR
    set proto_xml_files_=
    set process_dir_=%%d
    
    echo Process dir [!cur_path_!!process_dir_!]
    
    for %%i in (!process_dir_!*_proto*.xml) do (
        :: �������ۼӱ���ʹ��!
        set proto_xml_files_=!proto_xml_files_! %%i
    )
    echo show xmlfile[ !proto_xml_files_!]    
    !tdr_cmd_! --xml2cpp -pl -O !process_dir_! !proto_xml_files_!
    if not %ERRORLEVEL% == 0 goto label_error_pocess

)

::--------------------------------------------------------------------------------------------
:label_right_exit
::�����˳�
endlocal
cd %cur_path_%
exit /b 0

::--------------------------------------------------------------------------------------------
::�˳����Ƶ�
:label_error_pocess
endlocal
cd %cur_path_%
exit /b 110

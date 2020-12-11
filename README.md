# UTAU-Multisampler
UTAU Multi-resampler helper

- Multisampler（多重采样器）


- 功能

本身不具有重采样功能，可以通过Flags链接其他重采样器的辅助工具。



-准备

首先在“C:\ProgramData\UTAU Plugin\Multisampler”目录中新建一个文本文档，在里面输入以下内容并保存为config.ini，编码选择ANSI。

————————————————————————————

[Settings]
Prefix=r
Default=1

[Resamplers]
0=D:\UTAU\resampler.exe
1=D:\UTAU\tools\moresampler.exe
2=D:\UTAU\tools\TIPS.exe
3=D:\UTAU\tools\tn_fnds.exe

————————————————————————————

“Resamplers”下方是Multisampler可以读取的重采样器的路径（必须是绝对路径），按照这个格式可以添加任意多个重采样器，序号必须从0开始，依次递增，必须是连续的自然数。

“Settings”下方是默认设置。

“Prefix”是Multisampler的Flags，默认是“r”，可以自行修改，Flags“r0”表示使用序号为0的重采样器。

“Default”是默认使用的重采样器序号（该重采样器必须是“Resamplers”下方指定的）。


- 用法（以“r”为例）

在UTAU中，工程属性中将第二个工具（Tool 2 Resample）设为Multisampler（Multisampler可以放在任意位置）。

如果UST全局要使用某个重采样器（如序号为1的重采样器），可以在工程属性的输出选项中添加全局Flags“r1”，如果添加了多个“r”参数，则后面的会全部被忽略。

如果全局没有添加“r”参数，那么全局使用“Default”指定的重采样器。

如果某个音符要使用其他重采样器（如序号为2的重采样器），可以在这个音符的Flags中添加“r2”，如果添加了多个“r”参数，则后面的会全部被忽略。

同时，一个音符一旦添加“r”参数（不管是否有效），那么全局Flags将对它不起作用。

如果音符添加了“r”参数，但是该序号的重采样器不存在（无效），那么使用全局重采样器。

如果全局添加了“r”参数，但是该序号的重采样器不存在（无效），那么使用“Default”指定的重采样器。

如果“Default”指定的重采样器也不存在，那么Multisampler将会停止工作。

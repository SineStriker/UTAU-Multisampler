# UTAU-Multisampler
UTAU Multi-resampler helper

## Description
There is no resampling function in itself, but other resampler can be linked through Flags.

## Preparation
1. Create a new text file in the directory "C:\ProgramData\UTAU Plugin\Multisampler".
2. You may need to add the subdirectories manually.
3. Input lines like following and save as "config.ini".
4. The charset must be ANSI.

```
[Settings]
Prefix=r
Default=1

[Resamplers]
0=D:\UTAU\resampler.exe
1=D:\UTAU\tools\moresampler.exe
2=D:\UTAU\tools\TIPS.exe
3=D:\UTAU\tools\tn_fnds.exe
```

## Instructions
*Below "Resamplers" is the path of the resamplers that Multisampler can detect(must be the absolute path). Resamplers can be added in this format. The serial number must start from 0 and increase successively, and must be a continuous natural number.
*Below "Settings" are the default Settings。
*"Prefix" is the **Flags** of Multisampler, the default is ***"r"*** and can be modified by yourself. ***"r0"*** means using a resampler of number 0.
*"Default" is the resamplers number used by default (the resamplers must be specified below "Resamplers").

## How To Use
Suppose the **Prefix** is ***"r"***

Change the **"Tool 2(Resample)"** to Multisampler (Multisampler can be placed anywhere) in project property of UTAU.

If you want to use a resampler globally (such as a resampler of number 1), global Flags ***"r1"*** can be added to the output option of the project property. If more than one ***"r"*** arguments are added, the rest will be ignored.

If the "R" parameter is not added globally, the resampler specified by "Default" will be used globally.

If you want to use another resampler to render a certain note (such as a resampler of number 2), add ***"r2"*** to the Flags of this note. If more than one ***"r"*** arguments are added, the rest will be ignored.

Meanwhile, once an ***"r"*** argument (valid or not) is added to the note, global Flags will be ignored on this note.

If a note has an ***"r"*** parameter added, but the resampler specified by this Flag does not exist (invalid), then the global resampler will be used on this note.

If the project has an ***"r"*** parameter added，but the resampler specified by this Flag does not exist (invalid), then the default resampler will be used as global resampler.

If the resampler specified in "Default" needs using but does not exist (invalid), the Multisampler will stop working.

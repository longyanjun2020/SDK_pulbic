#!/usr/bin/perl

system("sed -i 's/Hook_cus.lib//' MStarStudio_UP/MStarKernel/App/XMMI/App_mmi_B3_cus.vcproj");
sleep(1);
system("sed -i 's/Profiler_cus.lib//' MStarStudio_UP/MStarKernel/App/XMMI/App_mmi_B3_cus.vcproj");

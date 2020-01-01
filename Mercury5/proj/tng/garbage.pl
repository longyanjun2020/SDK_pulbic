#!/usr/bin/perl

my $cnum = 0;
my $snum = 0;

my @reserveCfile = ();
my @save_files = ();

open(LOG_FILE, "> delNoMakFiles.txt") or die "cannot write\"delNoMakFiles.txt\" file\n";
if (-e "tng/release_process/releaseFiles.txt")
{
	open(SAVE_FILE, "tng/release_process/releaseFiles.txt");
	@save_files=<SAVE_FILE>;
	close(SAVE_FILE);
}
else
{
	print LOG_FILE "tng/release_process/releaseFiles.txt does not exist!\n";
}

my $filenum = 0;
sub remove
{
	my $pathname = shift;
	print "Enter path: $pathname\n";
	
	my @files = <*>;
	
	for my $path (@files)
	{
		if (-d $path)
		{
			chdir $path;
			remove("$pathname/$path");
			chdir "../";
		}
		else
		{
			if ($path =~ /\.c$/ || $path =~ /\.asm/)
			{
				my $found = 0;
				for my $reserve (@reserveCfile)
				{
					if($path eq $reserve)
					{
						$found = 1;
					}
				}
				for my $saveFile (@save_files)
				{
					$saveFile =~ s/\x0d\x0a//ig;
					if($saveFile =~ /$path$/)
					{
						$found = 1;
					}
				}
				if($found)
				{
					print "Reserve file: $path\n";
				}
				else
				{
					$filenum += 1;
					unlink $path;
					print "remove $pathname/$path\n";
					print LOG_FILE "remove $pathname/$path\n";
				}
			}
		}
	}
}

my $scdir = shift;

chdir "$scdir";
remove("$scdir");

print "Total deleted files $filenum C and S files \n";
close (LOG_FILE);	

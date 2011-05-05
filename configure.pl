#!/usr/bin/perl
use File::Basename;
use FindBin;

sub find_cpp {
	my ($dir, $result) = @_;
	$result ||= {};
	
	my @subdirs = ();
	
	opendir DIR, $dir or die "$dir: $!";
	
	while ($_ = readdir DIR) {
		next if /^\.\.?$/;
		
		if (-d "$dir/$_") {
			push @subdirs, $_;
		} elsif (/\.cpp$/) {
			$result->{"$dir/$_"} = 1;
		}
	}
	
	closedir DIR;
	find_cpp("$dir/$_", $result) foreach @subdirs;
	return $result;
}

sub find_dep {
	my ($file, $result) = @_;
	$result ||= {};
	
	my %dep = ();
	
	open IN, $file or die "$file: $!";
	
	while (<IN>) {
		if (/^\s*#\s*include\s+"(.*?)"/) {
			$dep{$1} = 1;
		}
	}
	
	close IN;
	
	my $dir = dirname($file);
	
	for (keys %dep) {
		unless ($result->{"$dir/$_"}) {
			$result->{"$dir/$_"} = 1;
			find_dep("$dir/$_", $result);
		}
	}
	
	return $result;
}

sub get_rel_path {
	my ($file) = @_;
	return substr($file, length($FindBin::Bin) + 1);
}

sub get_obj_file {
	my ($file) = @_;
	return 'obj/'.substr($file, length($FindBin::Bin) + 1, -4).'.o';
}

my $c_files = find_cpp($FindBin::Bin);
my @c_files = sort keys %$c_files;

my $obj_list = join ' ', map {
	get_obj_file($_)
} grep {get_rel_path($_) !~ m{^tests/}} @c_files;

my $tests_obj_list = join ' ', map {
	get_obj_file($_)
} grep {get_rel_path($_) ne 'main.cpp'} @c_files;

open OUT, ">$FindBin::Bin/Makefile" or die "Makefile: $!";
binmode(OUT);

print OUT <<END;
all: bin/cppmines.exe bin/cppmines-tests.exe

bin/cppmines.exe: $obj_list
	mkdir -p bin
	g++ -Wall -o \$\@ $obj_list

bin/cppmines-tests.exe: $tests_obj_list
	mkdir -p bin
	g++ -Wall -o \$\@ $tests_obj_list

END

for my $c_file (@c_files) {
	my $c_path = get_rel_path($c_file);
	my $obj_path = get_obj_file($c_file);
	my $h_files = find_dep($c_file);
	my @h_files = sort keys %$h_files;
	
	my $h_list = join ' ', (map {
		get_rel_path($_)
	} @h_files);
	
	my $obj_parent = dirname($obj_path);
	
	print OUT <<END;
$obj_path: $c_path $h_list
	mkdir -p $obj_parent
	g++ -c -Wall -o \$\@ $c_path

END
}

print OUT <<END;
run: bin/cppmines.exe
	bin/cppmines.exe

test: bin/cppmines-tests.exe
	bin/cppmines-tests.exe

clean:
	rm -rf bin obj
END

close OUT;

print "done\n";

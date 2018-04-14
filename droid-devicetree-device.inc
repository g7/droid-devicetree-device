%if 0%{!?final_dtb:1}
%define final_dtb %{master_dts}.dtb
%endif

%if 0%{!?includes_directory:1}
%define includes_directory "include"
%endif

Name:          droid-devicetree-%{device}
Summary:       Custom devicetree for %{device}
Version:       0
Release:       1
Group:         System
License:       BSD-3-Clause
BuildRequires: dtc
BuildRequires: cpp

%description
%{summary}

%build
cpp -nostdinc -I %{includes_directory} -undef -x assembler-with-cpp %{master_dts} > %{master_dts}.preprocessed
dtc -O dtb -b 0 -o %{final_dtb} %{master_dts}.preprocessed

%install
mkdir -p $RPM_BUILD_ROOT/usr/lib/devicetrees
install -m755 %{final_dtb} $RPM_BUILD_ROOT/usr/lib/devicetrees

%files
/usr/lib/devicetrees/*

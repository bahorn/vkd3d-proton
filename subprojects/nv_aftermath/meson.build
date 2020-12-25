project('nv-aftermath')

# Based of the second solution in the answer to:
# https://stackoverflow.com/questions/61058722/how-can-i-specify-library-path-when-using-meson

aftermath_lib = 'aftermath'
aftermath_header_dir = './include'
# Fix this.
aftermath_lib_dir = './external/windows/lib/x64'

nv_aftermath_dep = declare_dependency(
  include_directories : include_directories(aftermath_header_dir),
  link_args           : [ '-L' + aftermath_lib_dir, '-l' + aftermath_lib])

#!/bin/bash
# prints relative path of src_path file/dir from dst_dir point of view (for creation of symlink for example)
#     . relative.sh
#     relative src_path dst_dir

relative() {
	src_path=$1
	dst_dir=$2
	[ -z "$src_path" ] || [ -z "$dst_dir" ] && echo "wrong parameters | src_path: $src_path; dst_dir: $dst_dir" \
		&& return 1

	python -c "import os.path; print(os.path.relpath('$src_path', '$dst_dir'))"
	return 0
}

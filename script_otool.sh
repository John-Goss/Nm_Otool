#! /bin/bash
diff <(./ft_otool $@) <(otool -t $@)

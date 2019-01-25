for file in `ls -1 tests/input | cut -d . -f1`
do	
	echo "'"$file".s':    {'error': False,  'error_type': None, 'error_line': -1},"
done

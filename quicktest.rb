# example to test didimama

open = 'data/file1.pdb'
close= 'data/file2.pdb'
output = 'matrix.csv'

exename = './didimama'
switcha = ' -a '
switchb = ' -b '

a = exename + switcha + open + switchb + close + ' > ' + output

system a

puts a
puts 'open  file = ' + open
puts 'close file = ' + close
puts 'output is ' + open + ' - ' + close


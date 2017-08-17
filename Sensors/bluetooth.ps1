"Sensor Data`n" | Set-Content 'data.txt'

$port=new-Object System.IO.Ports.SerialPort COM15,9600,none,8,one
$port.open()

$port.WriteLine("Port is opened, listening for data...")

$input=$true
$dataRead=$false
while ($input) {
  $line=$port.ReadLine()
  if($dataRead) {
    $line | Add-Content 'data.txt'
    $port.WriteLine("OK")
    $dataRead=$false
  }
  elseif ($line -eq "s") {
    $dataRead=$true
    $port.WriteLine("OK")
  }
  elseif ($line -eq "e") {
    $input=$false
  }
  else {
    $port.WriteLine("Error: Command not recognized")
  }
}
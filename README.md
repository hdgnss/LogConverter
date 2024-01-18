# LogConverter

A very simple tool to convert GPS logs to NMEA file. 


## Convert GPS log
```
LogConverter -i aa.log -o aa.nmea
```
or without -o, it will create the same filename with `.nmea` extension as the input file.

```
LogConverter -i aa.log
```

## Convert GPS log use grep
```
LogConverter -g -i aa.log -o aa.nmea
```
or without -o, it will create the same filename with `.nmea` extension as each input file.

```
LogConverter -g -i aa.log
```

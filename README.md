# database
Trabajo Práctico 2 - 75.59 Técnicas de Programación Concurrente I (FIUBA)

### Build
To build the project you can use the script 
```sh
$ ./build.sh
```
This will create a `build` directory with the `server` and `client` executables.

### Command line arguments

## Server
- **DB file**  
Database persistence file.

## Client
The client takes no arguments

### Execution examples

## Server
```sh
$ ./build/server build/db.txt
```

## Client
```sh
$ ./build/client
```

### Usage
```
Make a query (insert <name,address,phone>, select <name,address,phone>) or just exit.
> insert Sherlock Holmes,Baker Street 221B,58859989
Success
> select sherlock holmes,,
1 results.
Sherlock Holmes,Baker Street 221B,58859989
>
> exit
```

### License
GNU General Public License v3.0

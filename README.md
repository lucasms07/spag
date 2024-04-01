# spag
spag (Simple PAssword Generator) is a simple command-line password generator written in C.
By default, it prints to standard output a 16 character random password, that can include majuscules, minuscules, numbers and symbols.

## Install
```sh
# clone the repo
git clone https://github.com/lucasms07/spag.git

# enter the spag directory
cd spag/

# compile and install
sudo make install
```

## Usage
```sh
# generate a 16 character password
spag

# generate a password without any numbers
spag -n

# generate a password without any symbols
spag -s

# generate a password that only has letters
spag -ns

# generate a password that only has numbers
spag -mMs

# generate 5 passwords with 32 characters each
spag -q 5 -t 32
```

## Uninstall
```sh
# make sure you're inside the spag directory and run
sudo make uninstall
```

## License
spag is free and unencumbered public domain software.
For more information, see the accompanying [UNLICENSE](./UNLICENSE) file.

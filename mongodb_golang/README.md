# mongodb golang test

## mongodb server

```bash
# install mongodb server (on macOS)
brew tap mongodb/brew
brew install mongodb-community@6.0


# start mongodb
brew services start mongodb-community@6.0

# stop mongodb
brew services start mongodb-community@6.0

# install compass(the GUI for MongoDB)
https://downloads.mongodb.com/compass/mongodb-compass-1.33.1-darwin-x64.dmg

# compass > cmd+n > new connect
mongodb://localhost:27017

# compass > create database "my_coll" > create collection "my_coll"
```

## build and run

```bash
go get -u ./...
go run ./main.go
```

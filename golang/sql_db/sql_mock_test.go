package main

import (
	"fmt"
	"log"
	"testing"

	"github.com/DATA-DOG/go-sqlmock"
	"gorm.io/driver/mysql"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"
)

type User struct {
	ID   uint
	Name string
}

func NewMockMysql() (*gorm.DB, sqlmock.Sqlmock) {
	db, mock, err := sqlmock.New()
	if err != nil {
		log.Fatal(err)
	}
	gormDB, err := gorm.Open(mysql.New(mysql.Config{
		Conn:                      db,
		SkipInitializeWithVersion: true,
	}), &gorm.Config{
		Logger: logger.Default.LogMode(logger.Info),
	})
	if err != nil {
		log.Fatal(err)
	}
	return gormDB, mock
}

// https://www.codingexplorations.com/blog/testing-gorm-with-sqlmock
func TestGorm(t *testing.T) {
	db, mock := NewMockMysql()

	mock.ExpectBegin()
	mock.ExpectExec("^INSERT INTO `users` (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	mock.ExpectCommit()
	user := User{Name: "Jane Doe"}
	if err := db.Create(&user).Error; err != nil {
		t.Fatalf("Failed to insert user: %v", err)
	}

	rows := sqlmock.NewRows([]string{"id", "name"}).AddRow(1, "John Doe")
	mock.ExpectQuery("^SELECT \\* FROM `users`$").WillReturnRows(rows)
	var users []User
	if err := db.Find(&users).Error; err != nil {
		t.Fatalf("Error in finding users: %v", err)
	}
	fmt.Println("-------", users)
	if len(users) != 1 || users[0].Name != "John Doe" {
		t.Fatalf("Unexpected user data retrieved: %v", users)
	}

	mock.ExpectBegin()
	mock.ExpectExec("^UPDATE `users` SET `name`=(.+) WHERE (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	mock.ExpectCommit()
	user = User{ID: 1, Name: "Jane Smith"}
	if err := db.Save(&user).Error; err != nil {
		t.Fatalf("Failed to update user: %v", err)
	}

	mock.ExpectBegin()
	mock.ExpectExec("^DELETE FROM `users` WHERE (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	mock.ExpectCommit()
	user = User{ID: 1}
	if err := db.Delete(&user).Error; err != nil {
		t.Fatalf("Failed to delete user: %v", err)
	}
}

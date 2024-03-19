package main

import (
	"fmt"
	"testing"

	"github.com/DATA-DOG/go-sqlmock"
)

type User struct {
	ID   uint
	Name string
}

// https://www.codingexplorations.com/blog/testing-gorm-with-sqlmock
func TestGorm(t *testing.T) {
	db, mock := NewMockMysql()

	mock.ExpectExec("^INSERT INTO `users` (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	user := User{Name: "Jane Doe"}
	if err := db.Create(&user).Error; err != nil {
		t.Fatalf("Failed to insert user: %v", err)
	}

	rows := sqlmock.NewRows([]string{"id", "name"}).AddRow(1, "John Doe")
	mock.ExpectQuery("^SELECT (.+) FROM `users`$").WillReturnRows(rows)
	var users []User
	if err := db.Find(&users).Error; err != nil {
		t.Fatalf("Error in finding users: %v", err)
	}
	fmt.Println("-------", users)
	if len(users) != 1 || users[0].Name != "John Doe" {
		t.Fatalf("Unexpected user data retrieved: %v", users)
	}

	mock.ExpectExec("^UPDATE `users` SET `name`=(.+) WHERE (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	user = User{ID: 1, Name: "Jane Smith"}
	if err := db.Save(&user).Error; err != nil {
		t.Fatalf("Failed to update user: %v", err)
	}

	mock.ExpectExec("^DELETE FROM `users` WHERE (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	user = User{ID: 1}
	if err := db.Delete(&user).Error; err != nil {
		t.Fatalf("Failed to delete user: %v", err)
	}
}

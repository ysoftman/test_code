package main

import (
	"fmt"
	"log"
	"testing"

	"github.com/DATA-DOG/go-sqlmock"
	"github.com/stretchr/testify/assert"
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

func TestGormCreate(t *testing.T) {
	db, mock := NewMockMysql()

	// gorm Create 가 Transaction  으로 처리되서 expectBegin , expectcommit 처리
	mock.ExpectBegin()
	mock.ExpectExec("^INSERT INTO `users` (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	mock.ExpectCommit()

	user := User{Name: "Jane Doe"}
	err := db.Create(&user).Error
	assert.Nil(t, err)
	assert.Equal(t, "Jane Doe", user.Name)
}

func TestGormFind(t *testing.T) {
	db, mock := NewMockMysql()

	rows := sqlmock.NewRows([]string{"id", "name"}).AddRow(1, "John Doe")
	mock.ExpectQuery("^SELECT \\* FROM `users`$").WillReturnRows(rows)

	var users []User
	err := db.Find(&users).Error
	fmt.Println("-------", users)
	assert.Nil(t, err)
	assert.Equal(t, 1, len(users))
	assert.Equal(t, "John Doe", users[0].Name)
}

func TestGormSave(t *testing.T) {
	db, mock := NewMockMysql()

	mock.ExpectBegin()
	mock.ExpectExec("^UPDATE `users` SET `name`=(.+) WHERE (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	mock.ExpectCommit()

	user := User{ID: 1, Name: "Jane Smith"}
	err := db.Save(&user).Error
	assert.Nil(t, err)
	assert.Equal(t, 1, int(user.ID))
	assert.Equal(t, "Jane Smith", user.Name)
}

func TestGormDelete(t *testing.T) {
	db, mock := NewMockMysql()

	mock.ExpectBegin()
	mock.ExpectExec("^DELETE FROM `users` WHERE (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	mock.ExpectCommit()
	user := User{ID: 1}
	err := db.Delete(&user).Error
	assert.Nil(t, err)
}

func TestGormFirstOrCreate(t *testing.T) {
	db, mock := NewMockMysql()

	// FirstOrCreate 조회 결과 없으면 생성
	mock.ExpectQuery("^SELECT \\* FROM `users` WHERE `name`=\\? ORDER BY `users`.`id` LIMIT \\?$").
		WithArgs("bill", 1).
		WillReturnRows(sqlmock.NewRows([]string{})) // 조회 결과가 없는 경우
	mock.ExpectBegin()
	mock.ExpectExec("^INSERT INTO `users` (.+)$").WillReturnResult(sqlmock.NewResult(1, 1))
	mock.ExpectCommit()

	user := User{Name: "bill"}
	result := db.Where("`name`=?", "bill").FirstOrCreate(&user)
	assert.Nil(t, result.Error)
	assert.Equal(t, int64(1), result.RowsAffected)
}

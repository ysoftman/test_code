package main

import (
	"context"
	"fmt"
	"log"
	"time"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
)

type MongoDBClient struct {
	Client *mongo.Client
}

func CreateMongoDBClient() *MongoDBClient {
	// mongodb://myDBReader:D1fficultP%40ssw0rd@mongodb0.example.com:27017/?authSource=admin
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()
	client, err := mongo.Connect(ctx, options.Client().ApplyURI("mongodb://localhost:27017"))
	if err != nil {
		log.Fatal("failed to connect...")
	}

	err = client.Ping(ctx, readpref.Primary())
	if err != nil {
		log.Fatal("failed to ping...")
	}

	return &MongoDBClient{
		Client: client,
	}
}

func (mc *MongoDBClient) AddDoc(doc interface{}) {
	r, err := mc.Client.Database("my_db").Collection("my_coll").InsertOne(context.TODO(), doc)
	if err != nil {
		log.Println("failed to add document", err.Error())
	}
	log.Println("---AddDoc result---", r)
}

func (mc *MongoDBClient) UpdateDoc(filter interface{}, updatedata interface{}) {
	_, err := mc.Client.Database("my_db").Collection("my_coll").UpdateOne(context.TODO(), filter, updatedata)
	if err != nil {
		log.Println("failed to update document", err.Error())
	}
	log.Println("---UpdateDoc result---")
}

func (mc *MongoDBClient) DeleteDoc(filter interface{}) {
	_, err := mc.Client.Database("my_db").Collection("my_coll").DeleteMany(context.TODO(), filter)
	if err != nil {
		log.Println("failed to add document", err.Error())
	}
	log.Println("---DeleteDoc result---")
}

func (mc *MongoDBClient) Find(filter interface{}, r interface{}) {
	// ascending sort by document _id
	opt1 := options.Find().SetSort(bson.D{{Key: "_id", Value: 1}})
	cursor, err := mc.Client.Database("my_db").Collection("my_coll").Find(context.TODO(), filter, opt1)
	if err != nil {
		log.Println("failed to find document", err.Error())
	}
	defer cursor.Close(context.TODO())
	// decode each document into r
	if err := cursor.All(context.TODO(), r); err != nil {
		log.Println("failed to decode document", err.Error())
	}
	log.Println("---Find result---")
}

type sampleData1 struct {
	Name   string `json:"name"`
	Number int    `json:"number"`
	Desc   string `json:"desc"`
}

type samepleDoc1 struct {
	ObjId  primitive.ObjectID `bson:"_id,omitempty"`
	Name   string             `json:"name"`
	Number int                `json:"number"`
	Desc   string             `json:"desc"`
}

func main() {
	c := CreateMongoDBClient()

	// insert documents
	for i := 1; i <= 10; i++ {
		doc := sampleData1{
			Name:   fmt.Sprintf("%v", time.Now().Local().Format(time.RFC3339)),
			Number: i,
			Desc:   "",
		}
		c.AddDoc(doc)
		filter := bson.D{{Key: "desc", Value: bson.D{{Key: "$eq", Value: ""}}}}
		update := bson.D{{Key: "$set", Value: bson.D{{Key: "desc", Value: "updated"}}}}
		c.UpdateDoc(filter, update)
	}

	num := 5
	// find documents where document.Number == num
	// filter := bson.D{{Key: "number", Value: bson.D{{Key: "$eq", Value: num}}}}
	// find documents where document.Number < num
	filter := bson.D{{Key: "number", Value: bson.D{{Key: "$gt", Value: num}}}}
	docs := make([]samepleDoc1, 0)
	c.Find(filter, &docs)
	for i := 0; i < len(docs); i++ {
		fmt.Printf("%v %v %v %v\n", docs[i].ObjId, docs[i].Name, docs[i].Number, docs[i].Desc)
	}

	filter = bson.D{{Key: "number", Value: bson.D{{Key: "$gt", Value: 0}}}}
	c.DeleteDoc(filter)
}

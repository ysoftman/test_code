// Serde is a framework for serializing and deserializing Rust data structures efficiently and generically.
extern crate serde_json;

use serde::{Deserialize, Serialize};
use serde_json::json;
use serde_json::Value;

#[derive(Serialize, Deserialize, Debug)]
struct Fruit {
    name: String,
    cost: u32,
    etc: Vec<String>,
}

fn main() {
    println!("Hello, world!");

    let data = r#"
    {
        "name": "John Doe",
        "age": 43,
        "phones": [
            "+44 1234567",
            "+44 2345678"
            ]
        }"#;
    // deserialize (unmarshal)
    let ser: Value = serde_json::from_str(data).unwrap();
    println!("{:?}", ser);
    println!("{}", ser["name"]);
    println!("{}", ser["age"]);
    println!("{}", ser["phones"][0]);
    println!("{}", ser["phones"][1]);
    // serialize
    println!("{}", ser.to_string());

    println!("-----");

    // json! 매크로를 사용하면 json 구조의 데이터를 바로 생성
    let base_cost = 50;
    let data2 = json!({
        "name": "orange",
        "cost": 100 + base_cost,
        "other" : {
            "USA" : ["lemon", "apple"]
        }
    });
    println!("{:?}", data2);
    println!("{}", data2["name"]);
    println!("{}", data2["cost"]);
    println!("{}", data2["other"]["USA"][0]);
    println!("{}", data2["other"]["USA"][1]);
    // serialize
    println!("{}", data2.to_string());

    println!("-----");

    // json -> struct
    // deserialize (unmarshal)
    let data = r#"
    {
        "name" : "fine-apple",
        "cost" : 500,
        "etc" : [ "aaa", "bbb"]
    }"#;
    let ft: Fruit = serde_json::from_str(data).unwrap();
    println!("{:?}", ft);
    println!("{:?}", ft.name);
    println!("{:?}", ft.cost);
    println!("{:?}", ft.etc[0]);
    println!("{:?}", ft.etc[1]);

    println!("-----");

    // struct -> json
    // serialize
    let ft_str = serde_json::to_string(&ft).unwrap();
    println!("{}", ft_str);
}

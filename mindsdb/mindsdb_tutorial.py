from mindsdb import *

# First we initiate MindsDB
mdb = MindsDB()

# We tell mindsDB what we want to learn and from what data
mdb.learn(
    from_data="https://raw.githubusercontent.com/mindsdb/mindsdb/master/docs/examples/basic/home_rentals.csv", # the path to the file where we can learn from, (note: can be url)
    predict='rental_price', # the column we want to learn to predict given all the data in the file
    model_name='home_rentals' # the name of this model
)


# use the model to make predictions
result = mdb.predict(predict='rental_price', when={'number_of_rooms': 2,'number_of_bathrooms':1, 'sqft': 1190}, model_name='home_rentals')

# you can now print the results
print('The predicted price is ${price} with {conf} confidence'.format(price=result.predicted_values[0]['rental_price'], conf=result.predicted_values[0]['prediction_confidence']))
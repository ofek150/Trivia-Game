import sqlite3

def connect_to_database():
    try:
        # Connect to the SQLite database
        conn = sqlite3.connect('TriviaDB.sqlite')
        print("Connected to the database.")
        return conn
    except sqlite3.Error as e:
        print("Error connecting to the database:", e)
        return None

def close_connection(conn):
    if conn:
        conn.close()
        print("Connection closed.")

def insert_questions(conn, questions):
    try:
        cursor = conn.cursor()
        # Insert the questions
        cursor.executemany('INSERT INTO Questions VALUES (?, ?, ?, ?, ?, ?, ?)', questions)
        conn.commit()
        print("Questions inserted successfully.")
    except sqlite3.Error as e:
        print("Error inserting questions:", e)
        conn.rollback()

def main():
    connection = connect_to_database()
    
    questions = [
        ("sports", "How long is a marathon?", "26.6 km", "2km", "42km", "1m", 3),
        ("sports", "What is the only country to have played in every single soccer World Cup?", "brazil", "israel", "usa", "russia", 1),
        ("sports", "How many sports were included in the 2008 Summer Olympics?", "0", "44", "-4", "28", 4),
        ("sports", "What retired basketball player tried out for the Chicago White Sox in 1994?", "Michael Jordan", "deni avdia", "daniel mordukhovich", "dvir profus", 1),
        ("sports", "What team owns the longest winning streak in NBA history?", "LA Lakers", "maccabi tel aviv", "washington wizards", "hapoel beer sheva", 1),
        ("sports", "What is the record for red cards given in a single soccer game?", "30", "12", "36", "12331", 3),
        ("sports", "What type of race is the Tour de France?", "swimming race", "running race", "talking race", "Bicycle race", 4),
        ("sports", "What African country was the first ever to qualify for a World Cup?", "israel", "usa", "egypt", "south africa", 3),
        ("sports", "What was the first city to host the Olympics twice?", "paris", "tel aviv", "Los Angeles", "beer sheva", 1),

        ("General", "What does “www” stand for in a website browser?", "World Wide Web", "why when what", "where were we", "what what what", 1),
        ("General", "How long is an Olympic swimming pool (in meters)?", "21.236853423235km", "50cm", "100cm", "50m", 4),
        ("General", "! What countries made up the original Axis powers in World War II?", "israel", "germany", "italy", "japan", 1),
        ("General", "Which country do cities of Perth, Adelaide & Brisbane belong to?", "israel", "australia", "tel aviv", "NPC land", 2),
        ("General", "What geometric shape is generally used for stop signs?", "Octagon", "square", "triangle", "line", 1),
        ("General", "cynophobia is fear of____?", "water", "death", "insects", "dogs", 4),
        ("General", "What is the name of the biggest technology company in South Korea?", "apple", "samsung", "xiaomi", "lg", 2),
        ("General", "Which animal can be seen on the Porsche logo?", "dog", "kitty", "horse", "human", 3),

        ("Geography", "Which country has the largest population in the world?", "israel", "india", "usa", "china", 4),
        ("Geography", "What is not one of the continents of the world?", "Asia", "israel", "Antarctica", "Europe", 2),
        ("Geography", "What is the name of the longest river in Africa?", "Nile River", "nilus river", "naile river", "goat river", 1),
        ("Geography", "What is the capital of Mexico?", "tel aviv", "los angeles", "mexico city", "brazil", 3),
        ("Geography", "What is the name of the largest country in the world?", "russia", "israel", "usa", "india", 1),
        ("Geography", "Where is the Eiffel Tower located?", "paris", "washington DC", "mexico city", "tel aviv", 1),
        ("Geography", "What country has the most natural lakes?", "canada", "israel", "brazil", "mexico", 1),
        ("Geography", "How many States does the United States consist of?", "10", "50000", "50", "-23.4", 3)
    ]

    # Insert the questions into the database
    insert_questions(connection, questions)

    close_connection(connection)

if __name__ == "__main__":
    main()

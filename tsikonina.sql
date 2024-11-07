CREATE TABLE IF NOT EXISTS recipes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    meal_id TEXT,
    meal TEXT,
    drink_alternate TEXT,
    category TEXT,
    area TEXT,
    instructions TEXT,
    meal_thumb TEXT,
    tags TEXT,
    youtube TEXT,
    ingredients TEXT,
    measures TEXT,
    source TEXT,
    image_source TEXT,
    creative_commons_confirmed TEXT,
    date_modified TEXT
);

CREATE TABLE IF NOT EXISTS mainmenu (
id integer PRIMARY KEY AUTOINCREMENT,
title text NOT NULL,
url text NOT NULL
);

CREATE TABLE IF NOT EXISTS posts (
id integer PRIMARY KEY AUTOINCREMENT,
name of competition text NOT NULL,
date date NOT NULL,
organizer text NOT NULL,
place text NOT NULL,
number number NOT NULL,
type text NOT NULL
);
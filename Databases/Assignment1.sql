drop database ForeignMusic
create database ForeignMusic
go
use ForeignMusic
go

CREATE TABLE Song
(sid CHAR(10),
name VARCHAR(20),
length INT,
alid CHAR(10),
pid CHAR(10)
)

CREATE TABLE Artist
(aid CHAR(10),
afirstname VARCHAR(20),
asecondname VARCHAR(20),
nationality VARCHAR(20)
)
 DROP TABLE Song
 CREATE TABLE Song
(sid CHAR(10),
name VARCHAR(20),
length INT,
alid CHAR(10),
pid CHAR(10),
PRIMARY KEY(sid)
)

DROP TABLE Artist
CREATE TABLE Artist
(aid CHAR(10),
afirstname VARCHAR(20),
asecondname VARCHAR(20),
nationality VARCHAR(20),
PRIMARY KEY(aid)
)

CREATE TABLE Performs
(sid CHAR(10),
 aid CHAR(10),
 PRIMARY KEY(sid, aid)
)
ALTER TABLE Performs
ADD CONSTRAINT Fk_Performs_Song FOREIGN KEY(sid) REFERENCES Song(sid)

ALTER TABLE Performs
ADD CONSTRAINT Fk_Performs_Artist FOREIGN KEY(aid) REFERENCES Artist(aid)

CREATE TABLE Music_Company
(mcid CHAR(10),
mcname VARCHAR(20),
mccountry VARCHAR(20),
PRIMARY KEY(mcid)
)

ALTER TABLE Artist
ADD mcid CHAR(10)

ALTER TABLE Artist
ADD CONSTRAINT Fk_Artist_Music_Company FOREIGN KEY(mcid) REFERENCES Music_Company(mcid)

ALTER TABLE Artist
ADD lcid CHAR(10)

CREATE TABLE Label_Company
(lcid CHAR(10),
lcname VARCHAR(20),
PRIMARY KEY(lcid)
)

ALTER TABLE Artist
ADD CONSTRAINT Fk_Artist_Label_Company FOREIGN KEY(lcid) REFERENCES Label_Company

ALTER TABLE Artist
DROP COLUMN nationality

ALTER TABLE Artist
ADD anationality VARCHAR(20)

CREATE TABLE Producer
(pid CHAR(10),
pfirstname VARCHAR(20),
psecondname VARCHAR(20),
PRIMARY KEY(pid)
)

ALTER TABLE Song
ADD CONSTRAINT Fk_Song_Producer FOREIGN KEY(pid) REFERENCES Producer

CREATE TABLE Album
(alid CHAR(10),
alname VARCHAR(20),
allength INT,
PRIMARY KEY(alid))

ALTER TABLE Song
ADD CONSTRAINT Fk_Song_Album FOREIGN KEY(alid) REFERENCES Album

CREATE TABLE Genre
(gid CHAR(10),
gname VARCHAR(20),
PRIMARY KEY(gid))

CREATE TABLE Is_of
(sid CHAR(10),
gid CHAR(10),
PRIMARY KEY(sid, gid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(gid) REFERENCES Genre(gid))

CREATE TABLE Writer
(wid CHAR(10),
wfirstname VARCHAR(20),
wsecondname VARCHAR(20),
PRIMARY KEY(wid))

CREATE TABLE Written_by
(sid CHAR(10),
wid CHAR(10),
PRIMARY KEY(sid, wid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(wid) REFERENCES Writer(wid))

CREATE TABLE Language
(lid CHAR(10),
lname VARCHAR(20),
PRIMARY KEY(lid)
)

CREATE TABLE Sung_in
(sid CHAR(10),
lid CHAR(10),
PRIMARY KEY(sid, lid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(lid) REFERENCES Language(lid))

CREATE TABLE Streaming_platform
(spid CHAR(10),
spname VARCHAR(20),
sptype VARCHAR(20),
PRIMARY KEY(spid))

CREATE TABLE Streamed_on
(sid CHAR(10), 
spid CHAR(10),
PRIMARY KEY(sid,spid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(spid) REFERENCES Streaming_platform(spid))

DROP TABLE Album
DROP TABLE Artist
DROP TABLE Genre
DROP TABLE Is_of
DROP TABLE Label_Company
DROP TABLE Language
DROP TABLE Music_Company
DROP TABLE Performs
DROP TABLE Producer
DROP TABLE Song
DROP TABLE Streamed_on
DROP TABLE Streaming_platform
DROP TABLE Sung_in
DROP TABLE Writer
DROP TABLE Written_by

CREATE TABLE Genre
(gid INT PRIMARY KEY,
name NVARCHAR(30))
DROP TABLE Genre

CREATE TABLE Writter
(wid INT PRIMARY KEY IDENTITY(1,1),
first_name NVARCHAR(30),
second_name NVARCHAR(30))

CREATE TABLE Genre
(gid INT PRIMARY KEY IDENTITY(1,1),
name NVARCHAR(30))

DROP TABLE Genre
CREATE TABLE Genre
(gid INT PRIMARY KEY IDENTITY(1,1),
name NVARCHAR(30) UNIQUE)

CREATE TABLE Language
(lid INT PRIMARY KEY IDENTITY(1,1),
lname NVARCHAR(30))

CREATE TABLE Streaming_platform
(spid INT PRIMARY KEY IDENTITY(1,1),
spname VARCHAR(30),
sptype VARCHAR(30))

CREATE TABLE Album
(alid INT PRIMARY KEY IDENTITY(1,1),
alname NVARCHAR(30) UNIQUE,
allength INT)


CREATE TABLE Producer
(pid INT PRIMARY KEY IDENTITY(1,1),
first_name NVARCHAR(30),
second_name NVARCHAR(30)
)

CREATE TABLE Song
(sid INT PRIMARY KEY IDENTITY(1,1),
sname NVARCHAR(50),
slength INT,
alid INT,
pid INT,
FOREIGN KEY(alid) REFERENCES Album(alid),
FOREIGN KEY(pid) REFERENCES Producer(pid))

CREATE TABLE Is_of
(sid INT,
gid INT,
PRIMARY KEY(sid, gid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(gid) REFERENCES Genre(gid)
)

CREATE TABLE Written_by
(sid INT,
wid INT,
PRIMARY KEY(sid, wid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(wid) REFERENCES Writter(wid))

CREATE TABLE Sung_in
(sid INT,
lid INT,
PRIMARY KEY(sid, lid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(lid) REFERENCES Language(lid))

CREATE TABLE Streamed_on
(sid INT,
spid INT,
PRIMARY KEY(sid, spid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(spid) REFERENCES Streaming_platform(spid))

CREATE TABLE Music_company
(mcid INT PRIMARY KEY IDENTITY(1,1),
mcname NVARCHAR(50) UNIQUE,
mccountry VARCHAR(30))

CREATE TABLE Label_company
(lcid INT PRIMARY KEY IDENTITY(1,1),
lcname NVARCHAR(30) UNIQUE)

CREATE TABLE Artist
(aid INT PRIMARY KEY IDENTITY(1,1),
first_name NVARCHAR(30),
second_name NVARCHAR(30),
nationality VARCHAR(30),
mcid INT,
lcid INT,
FOREIGN KEY(mcid) REFERENCES Music_company(mcid),
FOREIGN KEY(lcid) REFERENCES Label_company(lcid))

CREATE TABLE Performs_on
(sid INT,
aid INT,
PRIMARY KEY(sid, aid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(aid) REFERENCES Artist(aid))
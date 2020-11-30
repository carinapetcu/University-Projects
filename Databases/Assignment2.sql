---------------------------------------- Changing the initial table ---------------------------------
ALTER TABLE Album
ADD alltracks INT DEFAULT 0

ALTER TABLE Album
ADD UNIQUE(alname)

ALTER TABLE Producer
DROP COLUMN first_name

ALTER TABLE Producer
DROP COLUMN second_name

ALTER TABLE Producer
ADD name NVARCHAR(30) UNIQUE

DROP TABLE Performs_on
DROP TABLE Artist

ALTER TABLE Streaming_platform
ADD number_of_streams INT

CREATE TABLE Performers
(pid INT PRIMARY KEY IDENTITY(1,1),
pname NVARCHAR(50),
year_of_debut INT,
mcid INT,
lcid INT,
FOREIGN KEY(mcid) REFERENCES Music_company(mcid),
FOREIGN KEY(lcid) REFERENCES Label_company(lcid))

CREATE TABLE Performs_on
(sid INT,
pid INT,
PRIMARY KEY(sid, pid),
FOREIGN KEY(sid) REFERENCES Song(sid),
FOREIGN KEY(pid) REFERENCES Performers(pid)
)

ALTER TABLE Performers
ADD group_or_solo BIT

ALTER TABLE Performers
DROP COLUMN group_or_solo

ALTER TABLE Performers
ADD group_or_solo VARCHAR(10)

SELECT * FROM Performers

CREATE TABLE Artist
(aid INT PRIMARY KEY IDENTITY(1,1),
afname NVARCHAR(20),
asname NVARCHAR(20),
year_of_birth INT)

CREATE TABLE Consisting_of
(aid INT,
pid INT,
PRIMARY KEY(aid, pid),
FOREIGN KEY(aid) REFERENCES Artist(aid),
FOREIGN KEY(pid) REFERENCES Performers(pid))

DROP TABLE Consisting_of

EXEC sp_rename 'Consisting_of', 'Performing_as'

ALTER TABLE Artist
ADD known_as NVARCHAR(20)

--------------------------------------ASSIGNMENT 2--------------------------------------------

----- 1.Inserts
-- Inserting elements in the Producer table
INSERT INTO Producer(name) VALUES ('SUGA')
INSERT INTO Producer(name) VALUES ('Pdogg')
INSERT INTO Producer(name) VALUES ('Jonas Jonasson')
INSERT INTO Producer(name) VALUES ('Dua Lipa')

-- Inserting an element in the Song table
INSERT INTO Song(sname,slength, alid) VALUES ('Sowieso', 187, 10) -- violates referential integrity key constraints since the album id 10 does not exist
INSERT INTO Song(sname,slength, alid, pid) VALUES ('Interlude: Shadow', 260, 1, 1)
INSERT INTO Song(sname,slength, alid, pid) VALUES ('Dionysus', 249, 2, 2)
INSERT INTO Song(sname,slength, alid, pid) VALUES ('Boy With Luv', 230, 1, 2)
INSERT INTO Song(sname,slength, alid, pid) VALUES ('Vor í Vaglaskógi', 277, 3, 3)
INSERT INTO Song(sname,slength, alid, pid) VALUES ('Physical', 260, 5, 4)
INSERT INTO Song(sname,slength) 
VALUES ('Yukon',285), ('Mein Herz brennt',280), ('Sonne',272), ('Einmal',197), 
('Sowieso',187), ('Hazy shade of winter',198), ('Welcome to the Black Parade',315), ('Occidentali s Karma',218), 
('Viceversa',215), ('UNO',161), ('All for Us',193), ('Bohemian Rhapsody',355), 
('Don t stop me now',210), ('XS',201), ('Dynasty',188), ('Daechwita',226), 
('Perspektiva',231), ('Zenit',218), ('Répondez-moi',180), ('Nightmare',232)
INSERT INTO Song(sname,slength) VALUES ('Lit', 181), ('Soul', 179)


-- Adding elements in the Album table
INSERT INTO Album(alname, allength) VALUES ('MAP OF THE SOUL: 7', 4500)
INSERT INTO Album(alname, allength) VALUES ('MAP OF THE SOUL: PERSONA', 1560)
INSERT INTO Album(alname, allength) VALUES ('A / B', 2520)
INSERT INTO Album(alname, allength) VALUES ('D - 2', 1980)
INSERT INTO Album(alname, allength) VALUES ('Future Nostalgia', 2280)

-- Inserting elements in the Genre table
INSERT INTO Genre(name) VALUES ('Dance')
INSERT INTO Genre(name) VALUES ('R&B')
INSERT INTO Genre(name) VALUES ('Hip-Hop')
INSERT INTO Genre(name) VALUES ('K-Pop')
INSERT INTO Genre(name) VALUES ('Hard Rock')
INSERT INTO Genre(name) VALUES ('Soundtrack')


-- Inserting elements in the Artist table
INSERT INTO Artist(afname, asname, year_of_birth, known_as) 
VALUES ('Dua','Lipa',1995,'Dua Lipa'), ('JJ Julius','Son',1991,'')
INSERT INTO Artist(afname, asname, year_of_birth, known_as) 
VALUES ('Seokjin', 'Kim', 1992, 'Jin'), ('Namjoon','Kim',1994,'RM'), ('Yoongi','Min',1992,'SUGA, Agust D'),
 ('Jimin','Park',1995,'Jimin'), ('Taehyung','Kim',1995,'V'), 
('Jungkook','Jeon',1997,'Jungkook')
INSERT INTO Artist(afname, asname, year_of_birth, known_as) 
VALUES ('Till','Lindemann',1963,NULL), ('Mark','Ćwiertnia',1983,'Mark Forster'), ('Gerard Arthur','Way',1977,NULL), 
('Ka-yee(嘉爾)','Wang(王)',1994,'Jackson Wang'), 
('Francesco','Gabanni',1982,NULL), ('Ιlya(Илья)','Prusikin(Прусикин)',1983,'Ilich'), 
('Zendaya Maree','Stoermer Coleman',1996,'Zendaya'), ('Farrokh','Bulsara',1946,'Freddie Mercury')
INSERT INTO Artist(afname, asname, year_of_birth) VALUES ('Rina', 'Sawayama', 1990) 
INSERT INTO Artist(afname, asname, year_of_birth, known_as) VALUES ('Hoseok','Jung',1994,'J-Hope') 
INSERT INTO Artist(afname, asname, year_of_birth, known_as) VALUES ('Lay','Zhang',1991,'Lay') 
INSERT INTO Artist(afname, asname, year_of_birth, known_as) VALUES ('Ashley Nicolette', 'Frangipane', 1994, 'Halsey')

-- Inserting elements in the Performers table
INSERT INTO Performers(pname, year_of_debut, group_or_solo) VALUES
('Dua Lipa',2015,'solo'),('Kaleo',2012,'group'),('BTS',2013,'group'),
('Lindemann',2013,'group'),('Rammstein',1994,'group'),('Mark Forster',2007,'solo'),
('Gerard Way',2001,'solo'),('My Chemical Romance',2001,'group'),('Francesco Gabanni',2000,'solo'),
('Little Big',2013,'group'),('Zendaya',2009,'solo'),('Queen',1970,'group'),
('Rina Sawayama',2013,'solo')
INSERT INTO Performers(pname, year_of_debut, group_or_solo) VALUES
('Agust D',2010,'solo')
INSERT INTO Performers(pname, year_of_debut, group_or_solo) VALUES
('LAY',2012,'solo')
INSERT INTO Performers(pname, year_of_debut, group_or_solo) VALUES 
('S.A.R.S', 2006, 'group')
INSERT INTO Performers(pname, year_of_debut, group_or_solo) VALUES 
('Onuka', 2013, 'group'), ('Gjons Tears',2011,'solo')
INSERT INTO Performers(pname, year_of_debut, group_or_solo) VALUES 
('Halsey', 2012, 'solo')

-- Inserting elements in the Performing_as table
INSERT INTO Performing_as(aid, pid) VALUES
(8,1),(9,2),(10,3),(11,3),(12,3),(26,3),(14,3),(15,3),(16,3),(17,4),(17,5),(18,6),(19,7),(19,8),(21,9),(22,10),(23,11),(24,12),(25,13),(12,14)
INSERT INTO Performing_as(aid, pid) VALUES (27,15)
INSERT INTO Performing_as(aid, pid) VALUES (28,19)

-- Inserting element in the Performs_on table
INSERT INTO Performs_on(sid, pid) VALUES
(3,3),(4,3),(5,3),(5,19),(6,2),(7,1),
(9,4),(10,5),(11,5),(12,6),(13,6),(14,7),
(15,8),(18,10),(16,9),(17,9),(19,11),(20,12),
(21,12),(22,13),(23,13),(24,14),(25,16),(26,17),
(27,18),(28,19),(29,15),(30,15)

-- Inserting elements in the Language table
INSERT INTO Language(lname) VALUES
('English'),('Icelandic'),('German'),('Korean'),('Chinese'),('Italian'),
('Serbian'),('Ucrainian'),('French'),('Spanish'),('Japanese')

-- Inserting elements in the Sung_in table
INSERT INTO Sung_in(lid,sid) VALUES
(1,5),(1,7),(1,14),(1,15),(1,18),(1,19),(1,20),(1,21),(1,22),(1,23),
(2,6),(3,9),(3,10),(3,11),(3,12),(3,13),(4,3),(4,4),(4,5),(4,24),
(5,29),(5,30),(6,16),(6,17),(7,25),(8,26),(9,27),(10,18)

-- Inserting elements in the Genre table
INSERT INTO Genre(name) VALUES 
('Metal'),('Pop'),('Alternative'),('Soundrack'),('Rock'),('Mandopop'),('Electronic')
SELECT * FROM Genre

-- Inserting elements in the Is_of table
INSERT INTO Is_of(gid, sid) VALUES
(11,9),(11,10),(11,11),(12,7),(12,12),
(12,13),(12,16),(12,17),(12,18),(12,25),
(12,27),(13,6),(13,14),(13,15),(13,22),
(13,23),(13,28),(4,3),(4,4),
(4,5),(4,24),(14,19),(15,20),(15,21),(16,29),(16,30),(17,26)

-- Inserting elements in the Album table
INSERT INTO Album(alname, allength, alltracks) VALUES
('Skills in Pills',2700,11),('Mutter',2700,11),('Liebe',2880,13),
('TAPE',5640,23),('Greatest Hits',12420,51),('SAWAYAMA',2640,13),('LIT',2100,12)

-- Inserting elements in the Producer table
INSERT INTO Producer(name) VALUES
('Peter Tägtgren'),('Rammstein'),('Mark Ćwiertnia'),('Doug Mckean'),('Gerard Way'),
('Luca Chiaravalli'),('Mattei Cantaluppi'),('Labrinth'),('Queen'),('Kyle Shearer'),
('Clarence Clarity'),('Yevgen Filatov'),('Jeroen Swinnen'),('Benny Blanco')

-- Inserting elements in the Writter table
INSERT INTO Writter(first_name, second_name) VALUES
('Yoongi','Min'),('Namjoon','Kim'),('Hoseok','Jung'),
('Jonas','Jonasson'),('Dua','Lipa'),('Paul','Simon'),('Gerard','Way'),
('Francesco','Gabbani'),('Luca','Chiaravalli'),('Ilya','Prusikin'),('Labrinth',NULL),
('Freddie','Mercury'),('Rina','Sawayama'),('Yevgen','Filatov'),('Gjon','Maharremaj'),
('Jeroen','Swimmen'),('Halsey',NULL),('LAY',NULL)

-- Inserting elements in the Written_by
INSERT INTO Written_by(sid, wid) VALUES 
(3,1),(4,1),(5,1),(24,1),(3,2),(5,2),(4,3),(5,3),(6,4),(7,5),
(14,6),(15,7),(16,8),(17,8),(16,9),(18,10),(19,11),(20,12),(21,12),(22,13),
(23,13),(26,14),(27,15),(27,16),(28,17),(29,18),(30,18)


------ 2. Deleting elements
-- Deleting element from Song table
DELETE 
FROM Song
WHERE sid = 1

-- Deleting elements from Artist table
DELETE 
FROM Artist
WHERE year_of_birth = 1994 AND known_as LIKE 'J%'

DELETE FROM Artist
WHERE aid BETWEEN 1 AND 7

-- Deleting element from Song table
DELETE FROM Song
WHERE pid IS NULL AND slength < 150


------ 3. Updating elements
-- Updating elements in the Album table
UPDATE Album
SET alltracks = 10
WHERE alid = 3

UPDATE Album
SET alltracks = 11
WHERE alid = 5

UPDATE Album
SET alltracks = 20
WHERE alid = 1

UPDATE Album
SET alltracks = 7
WHERE alid = 2

UPDATE Album
SET alltracks = 10
WHERE alid = 4

-- Updating elements in the Artist table
UPDATE Artist
SET afname = 'Ilya',
asname = 'Prusikin'
WHERE known_as IN ('Ilich')

-- Updating elements in the Streaming_platform table
UPDATE Streaming_platform
SET sptype = 'paid'
WHERE sptype = 'free' OR spname <> 'Apple Music'

UPDATE Streaming_platform
SET sptype = 'free'
WHERE NOT spname = 'Spotify'

-- Updating elements in the Song table
UPDATE Song
SET alid = 7
WHERE sid = 9

UPDATE Song
SET alid = 8
WHERE sid = 10 OR sid = 11

UPDATE Song
SET alid = 9
WHERE sid = 12

UPDATE Song
SET alid = 10
WHERE sid = 13

UPDATE Song
SET alid = 11 
WHERE sid = 20 OR sid = 21

UPDATE Song
SET alid = 12
WHERE sid = 22 OR sid = 23

UPDATE Song
SET alid = 13
WHERE sid = 29 OR sid = 30

UPDATE Song
SET alid = 4
WHERE sid = 24

UPDATE Song
SET pid = 5
WHERE sid = 9

UPDATE Song
SET pid = 6 
WHERE sid = 10 OR sid = 11

UPDATE Song
SET pid = 7
WHERE sid = 12 OR sid = 13

UPDATE Song
SET pid = 8
WHERE sid = 14

UPDATE Song
SET pid = 9
WHERE sid = 15

UPDATE Song
SET pid = 10
WHERE sid = 16

UPDATE Song
SET pid = 11
WHERE sid = 17

UPDATE Song
SET pid = 12
WHERE sid = 19

UPDATE Song
SET pid = 13
WHERE sid = 20 OR sid = 21

UPDATE Song
SET pid = 14
WHERE sid = 22

UPDATE Song
SET pid = 15
WHERE sid = 23

UPDATE Song
SET pid = 16
WHERE sid = 26

UPDATE Song
SET pid = 17
WHERE sid = 27

UPDATE Song
SET pid = 18
WHERE sid = 28


----------------------------------------- QUERIES ------------------------------------------------------------
----- a. 2 queries with the union operation; use UNION [ALL] and OR
-- 1. UNION operation( also used AND in the WHERE clause) -> get the names and the band where they perform/ their stage name if they are solo of all
--						 the artists that are born before 1985 or after 1995
(SELECT A.afname AS first_name, A.asname AS second_name, P.pname AS performs_as
FROM Artist A, Performing_as PA, Performers P
WHERE A.year_of_birth < 1985 AND PA.aid = A.aid AND PA.pid = P.pid)
UNION
(SELECT A.afname AS first_name, A.asname AS second_name, P.pname AS performs_as
FROM Artist A, Performing_as PA, Performers P
WHERE A.year_of_birth > 1995 AND PA.aid = A.aid AND PA.pid = P.pid)

-- 2. OR operation(also used DISTINCT and conditions with AND in WHERE clause) -> get the name of the songs which are sang in German or English and have a length over 200 seconds
SELECT DISTINCT S.sname as song_name
FROM Song S, Sung_in SI, Language L
WHERE (S.sid = SI.sid AND S.slength > 200 AND SI.lid = L.lid AND (L.lname = 'English' OR L.lname = 'German'))

----- b. 2 queries with the intersection operation; use INTERSECT and IN
-- 1. INTERSECT operation(also used arithmetic expression in SELECT clauseand conditions with AND in WHERE clause) -> Find the stage name of all solo artists who were over 20 years 
--                                                                             old when they debuted and their age at that time
(SELECT P.pname AS stage_name, P.year_of_debut - A.year_of_birth AS debuting_age
FROM Performers P, Performing_as PA, Artist A
WHERE P.pid = PA.pid AND PA.aid = A.aid AND P.group_or_solo = 'solo')
INTERSECT
(SELECT P.pname AS stage_name, P.year_of_debut - A.year_of_birth AS debuting_age
FROM Performers P, Performing_as PA, Artist A
WHERE P.pid = PA.pid AND PA.aid = A.aid AND P.year_of_debut - A.year_of_birth > 20)

-- 2. IN operation(also used arithmetic expression in SELECT clause and conditions with AND in WHERE clause) ->
-- Find the average age of performers that have K-Pop songs
SELECT AVG(2020 - A.year_of_birth) AS Average_age
FROM Performers P, Artist A, Performing_as PA
WHERE A.aid = PA.aid AND P.pid = PA.pid AND P.pid IN
	(SELECT P1.pid
	FROM Performers P1, Performs_on PO, Song S
	WHERE P1.pid = PO.pid AND PO.sid = S.sid AND S.sid IN
		(SELECT S1.sid
		FROM Song S1, Is_of I, Genre G
		WHERE S1.sid = I.sid AND I.gid = G.gid AND G.name = 'K-Pop'
		))

----- c. 2 queries with the difference operation; use EXCEPT and NOT IN
-- 1. EXCEPT operation -> Get the name of all songs that have a length over 200 seconds and that are not sung in German
(SELECT S.sname as Song_name
FROM Song S
WHERE S.slength > 200)
EXCEPT
(SELECT S.sname
FROM Song S, Sung_in SI, Language L
WHERE S.sid = SI.sid AND SI.lid = L.lid AND L.lname = 'German')

-- 2. NOT IN operation(also used conditions with AND in WHERE clause) -> Get the name of all albums that are not in English
SELECT A.alname AS Album_name
FROM Album A, Song S
WHERE S.alid = A.alid AND S.sname NOT IN
	(SELECT S.sname
	FROM Song S, Sung_in SI, Language L
	WHERE S.sid = SI.sid AND SI.lid = L.lid AND L.lname = 'English')

----- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, FULL JOIN; one query will join at least 3 table, while another one will 
-----    join at least 2 many-to-many relationships
-- 1. INNER JOIN(also used ORDER BY) - Get the name of all the songs that are on an album, as well as the name of the album, sorted by the album
SELECT S.sname AS [Song name], A.alname AS [Album name] 
FROM Song S
INNER JOIN Album A ON S.alid = A.alid 
ORDER BY A.alname

-- 2. OUTER JOIN(also used ORDER BY and TOP) - Get the name of the first 10 songs and the album name(doesn't matter if they are on an album or not), 
--                                             sorted by their length
SELECT TOP 5 S.sname AS [Song name], A.alname AS [Album name]
FROM Song S
LEFT JOIN Album A ON S.alid = A.alid 
ORDER BY S.slength DESC

-- 3. RIGHT JOIN(also joined at least 3 tables, used DISTINCT and ORDER BY) - Get the distinct name of the albums and the genre they are, sorted by Genre
SELECT DISTINCT A.alname AS [Album name], G.name AS [Genre]
FROM Genre G
RIGHT JOIN Is_of IO ON G.gid = IO.gid
RIGHT JOIN Song S ON S.sid = IO.sid
RIGHT JOIN Album A ON A.alid = S.alid
ORDER BY G.name

-- 4. FULL JOIN(also used ORDER BY, DISTINCT AND it joined 3 many to many relationships) - Get the names of all Performers that also participated in 
--                                                                                         the process of writing a song, as well as the name of the song, 
--                                                                                         without duplicates and ordered by 
SELECT DISTINCT P.pname AS Name, S.sname AS Song
FROM Writter W
FULL JOIN Written_by WB ON W.wid = WB.wid
FULL JOIN Song S ON WB.sid = S.sid
FULL JOIN Performs_on PO ON S.sid = PO.sid
FULL JOIN Performers P ON P.pid = PO.pid
FULL JOIN Performing_as PA ON PA.pid = PO.pid
FULL JOIN Artist A ON A.aid = PA.aid
WHERE A.afname = W.first_name AND A.asname = W.second_name
ORDER BY P.pname


----- d. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery should include 
-----    a subquery in its own WHERE clause

-- 1. Get the distinct writters that wrote songs of the genre 'Pop' or 'K-Pop'
SELECT DISTINCT W.first_name as [First name], W.second_name as [Second Name], G.name as [Genre]
FROM Writter W
INNER JOIN Written_by WB ON W.wid = WB.wid
INNER JOIN Song S ON S.sid = WB.sid
INNER JOIN Is_of IO ON S.sid = IO.sid
INNER JOIN Genre G ON G.gid = IO.gid
WHERE G.gid IN(
	SELECT G1.gid
	FROM Genre G1
	WHERE G1.name = 'Pop' OR G1.name = 'K-Pop'
)

-- 2. Get the number of all Performers that are also Producers on songs which have over 200 seconds(also contains COUNT and a subquery containg a subquery)
SELECT COUNT(P.pname) AS [Number of performers/ producers]
FROM Performers P
WHERE P.pid IN(
	SELECT PO.pid
	FROM Performs_on PO
	WHERE PO.sid IN
	(
		SELECT S.sid
		FROM Song S
		INNER JOIN Producer PR ON S.pid = PR.pid
		WHERE S.slength > 200 AND PR.name = P.pname
	)
)

----- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause
-- 1. Get all the performers that have songs starting with D, grouped by Song decreasingly.
SELECT P.pname AS [Performer]
FROM Performers P
INNER JOIN Performs_on PO ON PO.pid = P.pid
WHERE EXISTS(
	SELECT S1.sname
	FROM Song S1
	WHERE S1.sid = PO.sid AND S1.sname LIKE 'D_%'
)

-- 2. Get the average age of the artists that have songs sang in Korean
SELECT DISTINCT AVG(2020 - A.year_of_birth) AS [Average Age]
FROM Artist A
INNER JOIN Performing_as PA ON PA.aid = A.aid
INNER JOIN Performers P ON P.pid = PA.pid
INNER JOIN Performs_on PO ON PO.pid = P.pid
INNER JOIN Song S ON PO.sid = S.sid
INNER JOIN Sung_in SI ON SI.sid = S.sid
WHERE EXISTS(
	SELECT L.lname
	FROM Language L 
	WHERE L.lid = SI.lid AND L.lname = 'Korean'
)

----- g. 2 queries with a subquery in the FROM clause                                        
-- 1. Get the performers which have songs with length > 200 and the albums where they have those songs and order them by the name of the album.
SELECT DISTINCT P.pname AS [Performer], m.alname AS [Album name]
FROM( Performers P INNER JOIN (
		SELECT PO.pid, A.alname
		FROM Song S, Album A, Performs_on PO
		WHERE S.slength > 200 AND A.alid = S.alid  AND PO.sid = S.sid
	) m ON m.pid = P.pid ) 
ORDER BY m.alname

-- 2. Get the first 10 albums sorted alphabetically and the language of each one of them.
SELECT DISTINCT TOP 10 A.alname AS [Album Name], m.lname AS [Language]
FROM(
		Album A LEFT JOIN(
			SELECT S.alid, L.lname
			FROM Song S, Sung_in SI, Language L
			WHERE S.sid = SI.sid AND SI.lid = L.lid
		) m ON m.alid = A.alid
)
ORDER BY A.alname

----- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause;
-----    use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;
-- 1. Get the album names and the percentage of songs added on each album(also used arithmetic expressions in the SELECT clause)
SELECT A.alname, COUNT(S.sname) *100/A.alltracks AS [Percentage of added songs]
FROM Song S, Album A
WHERE S.alid = A.alid
GROUP BY A.alname, A.alltracks

-- 2. Get the first name and the second name of all writters having written more than 1 song, ordered decreasingly by the number of songs

SELECT W.first_name AS [First name], W.second_name AS [Second name], COUNT(S.sid) AS [How many songs]
FROM Writter W
INNER JOIN Written_by WB ON W.wid = WB.wid
INNER JOIN Song S ON WB.sid = S.sid
GROUP BY W.first_name, W.second_name
HAVING COUNT(S.sid) > 1
ORDER BY [How many songs] DESC

-- 3. Get the genres and the count of the songs which have a average length over the overall average lengths

SELECT G.name AS [Genre], COUNT(S.sname) AS [Number of songs]
FROM Genre G
INNER JOIN Is_of IO ON IO.gid = G.gid
INNER JOIN Song S ON S.sid = IO.sid
GROUP BY G.name
HAVING AVG(S.slength) > (	
	SELECT AVG(S1.slength)
	FROM Song S1
)
ORDER BY [Number of songs] DESC

-- 4. Get the genres and the number of the albums of that certain genre where the maximum length of an album is smaller than the overall max length

SELECT G.name AS [Genre], COUNT(A.alname) AS [Number of albums]
FROM Genre G
INNER JOIN Is_of IO ON IO.gid = G.gid
INNER JOIN Song S ON S.sid = IO.sid
INNER JOIN Album A ON A.alid = S.alid
GROUP BY G.name
HAVING MAX(A.allength) < (	
	SELECT MAX(A1.allength)
	FROM Album A1
)
ORDER BY [Number of albums] DESC

----- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); rewrite 2 of them with aggregation operators, 
-----    and the other 2 with IN / [NOT] IN.
-- 1. Get all the performers that have at least a song of Genre Metal or Pop(also include the genre) and how many years has it been since they debuted(using ANY clause)
SELECT DISTINCT P.pname AS [Performer], G.name as [Genre], 2020 - P.year_of_debut AS [Years since debuting] 
FROM Performers P
INNER JOIN Performs_on PO ON PO.pid = P.pid
INNER JOIN Song S ON S.sid = PO.sid
INNER JOIN Is_of IO ON IO.sid = S.sid
INNER JOIN Genre G ON G.gid = IO.gid
WHERE G.name = ANY(
	SELECT G1.name
	FROM Genre G1
	WHERE G1.name = 'Metal' OR G1.name = 'Pop'
)
ORDER BY G.name

-- rewriting 1. using IN( ANY = <=> IN)

SELECT DISTINCT P.pname AS [Performer], G.name as [Genre], 2020 - P.year_of_debut AS [Years since debuting] 
FROM Performers P
INNER JOIN Performs_on PO ON PO.pid = P.pid
INNER JOIN Song S ON S.sid = PO.sid
INNER JOIN Is_of IO ON IO.sid = S.sid
INNER JOIN Genre G ON G.gid = IO.gid
WHERE G.name IN (
	SELECT G1.name
	FROM Genre G1
	WHERE G1.name = 'Metal' OR G1.name = 'Pop'
)
ORDER BY G.name

-- 2. Find the name, the second name of the oldest performer, as well as how many songs they have( using ANY clause)
SELECT P.pname as [Performer], 2020 - A.year_of_birth AS [Age], COUNT(S.sname) AS [Number of songs]
FROM Artist A
INNER JOIN Performing_as PA ON PA.aid = A.aid
INNER JOIN Performers P ON P.pid = PA.pid
INNER JOIN Performs_on PO ON PO.pid = P.pid
INNER JOIN Song S ON S.sid = PO.sid
WHERE A.year_of_birth = ANY(
	SELECT MIN(A1.year_of_birth)
	FROM Artist A1
)
GROUP BY P.pname, A.year_of_birth

-- rewriting 2. using aggregation
SELECT P.pname as [Performer], 2020 - A.year_of_birth AS [Age], COUNT(S.sname) AS [Number of songs]
FROM Artist A
INNER JOIN Performing_as PA ON PA.aid = A.aid
INNER JOIN Performers P ON P.pid = PA.pid
INNER JOIN Performs_on PO ON PO.pid = P.pid
INNER JOIN Song S ON S.sid = PO.sid
GROUP BY P.pname, A.year_of_birth
HAVING MIN(A.year_of_birth) = (
	SELECT MIN(A1.year_of_birth)
	FROM Artist A1
)

-- 3. Get all the distinct producers that have songs which are not of Pop genre, also get the genre and sort the result by the name of the genre( using ALL clause)
SELECT DISTINCT P.name as [Producer name], G.name AS [Genre]
FROM Producer P
INNER JOIN Song S ON S.pid = P.pid
INNER JOIN Is_of IO ON IO.sid = S.sid
INNER JOIN Genre G ON G.gid = IO.gid
WHERE G.name <>ALL(
	SELECT G1.name
	FROM Genre G1
	WHERE G1.name = 'Pop'
)
ORDER BY G.name

-- rewriting 3. using NOT IN( <>ALL <=> NOT IN) 
SELECT DISTINCT P.name as [Producer name], G.name AS [Genre]
FROM Producer P
INNER JOIN Song S ON S.pid = P.pid
INNER JOIN Is_of IO ON IO.sid = S.sid
INNER JOIN Genre G ON G.gid = IO.gid
WHERE G.name NOT IN(
	SELECT G1.name
	FROM Genre G1
	WHERE G1.name = 'Pop'
)
ORDER BY G.name


-- 4. Get the top 75% of the writters which have the minimum length of a song over the minimum overall length and order it by the first name( using ALL clause)
SELECT DISTINCT TOP 75 PERCENT W.first_name AS [First name], W.second_name AS [Second name]
FROM Writter W
INNER JOIN Written_by WB ON WB.wid = W.wid
INNER JOIN Song S ON S.sid = WB.sid
WHERE S.slength > ALL(
	SELECT MIN(S1.slength)
	FROM Song S1
)
ORDER BY W.first_name

-- rewriting 4. using aggregation

SELECT DISTINCT TOP 75 PERCENT W.first_name AS [First name], W.second_name AS [Second name]
FROM Writter W
INNER JOIN Written_by WB ON WB.wid = W.wid
INNER JOIN Song S ON S.sid = WB.sid
GROUP BY W.first_name, W.second_name
HAVING MIN(S.slength) > (
	SELECT MIN(S1.slength)
	FROM Song S1
)
ORDER BY W.first_name

SELECT * FROM Is_of
SELECT * FROM Song
SELECT * FROM Producer
SELECT * FROM Writter
SELECT * From Genre
SELECT * from Album
SELECT * FROM Artist
SELECT * FROM Performers
SELECT * FROM Performing_as
SELECT * FROM Performs_on
SELECT * FROM Language
SELECT * FROM Sung_in

SELECT * FROM Written_by
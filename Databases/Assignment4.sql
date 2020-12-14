------------------------------- VIEWS ------------------------------------------
ALTER TABLE Performers
ALTER COLUMN group_or_solo NVARCHAR(10)

----- view with a SELECT statement operating on one table
CREATE OR ALTER VIEW view_getAllSongs
AS
	SELECT *
	FROM Song
GO

----- view with a SELECT statement operating on at least 2 tables
CREATE OR ALTER VIEW view_getPerformersAndAlbumsWithSongs
AS
	SELECT DISTINCT P.pname AS [Performer], m.alname AS [Album name]
	FROM( Performers P INNER JOIN (
		SELECT PO.pid, A.alname
		FROM Song S, Album A, Performs_on PO
		WHERE S.slength > 200 AND A.alid = S.alid  AND PO.sid = S.sid
	) m ON m.pid = P.pid ) 
GO

----- view with a SELECT staetement that has a GROUP BY clause and operates on at least 2 tables
CREATE OR ALTER VIEW view_getAlbumNameAndPercentageOfAddedSongs
AS
	SELECT A.alname, COUNT(S.sname) AS [Number of added songs]
	FROM Song S, Album A
	WHERE S.alid = A.alid
	GROUP BY A.alname, A.alltracks
GO

----------------- ADD A NEW TEST ------------------------------------------------

CREATE OR ALTER PROC usp_addTables @tables VARCHAR(500), @testId INT, @noOfRows INT
AS
	DECLARE @position INT
	SET @position = 1

	DECLARE @tableName VARCHAR(50)

	DECLARE TablesCursor CURSOR FOR
	SELECT value
		FROM string_split(@tables, ',')
	OPEN TablesCursor
	FETCH TablesCursor
	INTO @tableName
	WHILE @@FETCH_STATUS = 0
	BEGIN
	
		DECLARE @tableId INT

		IF (SELECT COUNT(*) FROM Tables WHERE Tables.Name = @tableName) = 0
			INSERT INTO Tables VALUES (@tableName)

		SET @tableId = (SELECT Tables.TableID FROM Tables WHERE Tables.Name = @tableName)

		INSERT INTO TestTables VALUES(@testId, @tableId, @noOfRows, @position)
		SET @position = @position + 1

	FETCH TablesCursor
	INTO @tableName
	END
	CLOSE TablesCursor
	DEALLOCATE TablesCursor

GO

CREATE OR ALTER PROC usp_addViews @views VARCHAR(500), @testId INT
AS
	DECLARE @viewName VARCHAR(50)

	DECLARE ViewsCursor CURSOR FOR
	SELECT value
		FROM string_split(@views, ',')
	OPEN ViewsCursor
	FETCH ViewsCursor
	INTO @viewName
	WHILE @@FETCH_STATUS = 0
	BEGIN
	
		DECLARE @viewId INT

		IF (SELECT COUNT(*) FROM Views WHERE Views.Name = @viewName) = 0
			INSERT INTO Views VALUES (@viewName)

		SET @viewId = (SELECT Views.ViewID FROM Views WHERE Views.Name = @viewName)

		INSERT INTO TestViews VALUES(@testId, @viewId)

	FETCH ViewsCursor
	INTO @viewName
	END
	CLOSE ViewsCursor
	DEALLOCATE ViewsCursor

GO

CREATE OR ALTER PROC usp_addANewTest @testName VARCHAR(50), @tables VARCHAR(500), @views VARCHAR(500), @noOfRows INT
AS
	DECLARE @testId INT

	INSERT INTO Tests VALUES (@testName)
	SET @testId = (SELECT Tests.TestID FROM Tests WHERE Tests.Name = @testName)

	EXEC usp_addTables @tables, @testId, @noOfRows
	EXEC usp_addViews @views, @testId
GO

----------------- RUN A NEW TEST ------------------------------------------------

CREATE OR ALTER PROCEDURE usp_deleteDataFromTables @testId INT
AS
	DECLARE @tableName VARCHAR(50)
	DECLARE @tableId INT

	DECLARE TestTablesCursor CURSOR FOR
	SELECT T.Name, T.TableID
		FROM TestTables TB
		INNER JOIN Tables T ON TB.TableID = T.TableID 
		WHERE TB.TestID = @testId
		ORDER BY TB.Position 
	OPEN TestTablesCursor
	FETCH TestTablesCursor
	INTO @tableName, @tableId
	WHILE @@FETCH_STATUS = 0
	BEGIN

		DECLARE @deleteTable NVARCHAR(100)
		SET @deleteTable =N'DELETE FROM ' + @tableName
		EXEC (@deleteTable)
		IF (SELECT COUNT(col.is_identity)
				FROM sys.columns AS col
				INNER JOIN sys.tables AS tabel ON tabel.object_id = col.object_id
				INNER JOIN sys.types AS typ ON typ.system_type_id = col.system_type_id
				WHERE tabel.name = @tableName AND col.is_identity = 1) > 0
			DBCC CHECKIDENT (@tableName, RESEED, 0) 

	FETCH TestTablesCursor
	INTO @tableName, @tableId
	END
	CLOSE TestTablesCursor
	DEALLOCATE TestTablesCursor

GO

--- get the number of rows 
--- do a while where you add that number of rows
--- in each iteration we declare a query 
--- use a cursor to iterate through each column
---	check if the column is identity, otherwise leave it alone
---	if the column is int, generate a int using rand
---	if the column is nvarchar, generate a string have the format "random string number #[random_number]"
--- if the column is a foreign key, then set it to the currentRow
--- generate query having the format (value1,value2,...,valuen)

CREATE OR ALTER PROCEDURE usp_insertRowsInTable @tableName VARCHAR(50), @testId INT, @tableId INT
AS
	DECLARE @noOfRows INT
	SET @noOfRows = (SELECT TestTables.NoOfRows FROM TestTables WHERE TestTables.TestID = @testId AND TestTables.TableID = @tableId)

	DECLARE @index INT
	SET @index = 1

	DECLARE @columnName NVARCHAR(50)
	DECLARE @columnType NVARCHAR(50)
	DECLARE @isIdentity BIT

	WHILE @index <= @noOfRows
	BEGIN
		DECLARE @query NVARCHAR(500)
		SET @query = ' VALUES ('
		DECLARE @sentence NVARCHAR(250)
		SET @sentence = 'INSERT INTO ' + @tableName + '('
		
		DECLARE ColumnCursor CURSOR FOR
			SELECT DISTINCT col.name, typ.name, col.is_identity
				FROM sys.columns AS col
				INNER JOIN sys.tables AS tabel ON tabel.object_id = col.object_id
				INNER JOIN sys.types AS typ ON typ.system_type_id = col.system_type_id
				WHERE tabel.name = @tableName
		OPEN ColumnCursor
		FETCH ColumnCursor
		INTO @columnName, @columnType, @isIdentity
		WHILE @@FETCH_STATUS = 0
		BEGIN
			--- we check if it is a foreign key
			IF	(
					SELECT COUNT(*)
					FROM sys.foreign_key_columns fkc
					INNER JOIN sys.objects obj ON obj.object_id = fkc.constraint_object_id
					INNER JOIN sys.tables tab1 ON tab1.object_id = fkc.parent_object_id
					INNER JOIN sys.columns col1	ON col1.column_id = parent_column_id AND col1.object_id = tab1.object_id
					WHERE tab1.name = @tableName AND col1.name = @columnName ) > 0
					BEGIN
					SET @sentence = @sentence + @columnName
					SET @sentence = @sentence + ','
					SET @query = @query + (SELECT CAST(@index AS NVARCHAR))
					SET @query = @query + N','

					END
			ELSE
				--- we check if it is identity
				IF @isIdentity = 0
				BEGIN
				
					-- we check the type of the column
					IF @columnType = N'int'
					BEGIN
						-- we generate a random number using rand
						
						DECLARE @number INT
						SET @number = (SELECT RAND()*1500)
						SET @sentence = @sentence + @columnName
						SET @sentence = @sentence + ','
						SET @query = @query + (SELECT CAST(@number AS NVARCHAR))
						SET @query = @query + N','
					END
					
					
					IF @columnType = N'nvarchar'
					BEGIN
						
						DECLARE @random INT
						SET @random = (SELECT RAND()*1500)
						SET @sentence = @sentence + @columnName
						SET @sentence = @sentence + ','
						SET @query = @query + '''Random sentence number #'+(SELECT CAST(@random AS NVARCHAR)) + ''''
						SET @query = @query + N','
					END
					
				END
			
			FETCH ColumnCursor
			INTO @columnName, @columnType, @isIdentity
		END
		CLOSE ColumnCursor
		DEALLOCATE ColumnCursor

		SET @sentence =  substring(@sentence, 1, (len(@sentence) - 1))
		SET @sentence = @sentence + N')'
		SET @query =  substring(@query, 1, (len(@query) - 1))
		SET @query = @query + N')'
		SET @sentence = @sentence + ' ' + @query

		
		EXEC(@sentence)
		SET @index = @index + 1
	END
GO

CREATE OR ALTER PROCEDURE usp_insertDataFromTables @testId INT, @testRunId INT
AS
	DECLARE @tableName VARCHAR(50)
	DECLARE @tableId INT

	DECLARE @testRun INT
	SET @testRun = @testRunId

	DECLARE TestTablesCursor CURSOR FOR
	SELECT T.Name, T.TableID
		FROM TestTables TB
		INNER JOIN Tables T ON TB.TableID = T.TableID 
		WHERE TB.TestID = @testId
		ORDER BY TB.Position DESC
	OPEN TestTablesCursor
	FETCH TestTablesCursor
	INTO @tableName, @tableId
	WHILE @@FETCH_STATUS = 0
	BEGIN
		DECLARE @startAt datetime2
		SET @startAt = (SELECT CURRENT_TIMESTAMP)

		EXEC usp_insertRowsInTable @tableName, @testId, @tableId
		
		DECLARE @endAtTable datetime2
		SET @endAtTable = (SELECT CURRENT_TIMESTAMP)
		INSERT INTO TestRunTables VALUES (@testRun, @tableId, @startAt, @endAtTable)
	FETCH TestTablesCursor
	INTO @tableName, @tableId
	END
	CLOSE TestTablesCursor
	DEALLOCATE TestTablesCursor

GO

CREATE OR ALTER PROCEDURE usp_execViews @testId INT, @testRunId INT
AS
	
	DECLARE @viewName VARCHAR(50)
	DECLARE @viewId INT

	DECLARE @testRun INT
	SET @testRun = @testRunId

	DECLARE TestViewsCursor CURSOR FOR
	SELECT V.Name, V.ViewID
		FROM TestViews TV
		INNER JOIN Views V ON TV.ViewID = V.ViewID 
		WHERE TV.TestID = @testId
	OPEN TestViewsCursor
	FETCH TestViewsCursor
	INTO @viewName, @viewId
	WHILE @@FETCH_STATUS = 0
	BEGIN
		DECLARE @startAt datetime2
		SET @startAt = (SELECT CURRENT_TIMESTAMP)

		DECLARE @query NVARCHAR(200)
		SET @query = 'SELECT * FROM ' + @viewName

		EXEC(@query)

		DECLARE @endAt datetime2
		SET @endAt = (SELECT CURRENT_TIMESTAMP)
		INSERT INTO TestRunViews VALUES (@testRun, @viewId, @startAt, @endAt)
		

	FETCH TestViewsCursor
	INTO @viewName, @viewId
	END
	CLOSE TestViewsCursor
	DEALLOCATE TestViewsCursor

GO


CREATE OR ALTER PROCEDURE usp_testRun @testName VARCHAR(50)
AS
	DECLARE @testId INT
	SET @testId = (SELECT Tests.TestID FROM Tests WHERE Tests.Name = @testName)

	DECLARE @startAt datetime2
	SET @startAt = (SELECT CURRENT_TIMESTAMP)
	
	INSERT INTO TestRuns(Description, StartAt) VALUES(@testName, @startAt)

	DECLARE @testRunId INT
	SET @testRunId = @@IDENTITY

	EXEC usp_deleteDataFromTables @testId

	EXEC usp_insertDataFromTables @testId , @testRunId
	
	EXEC usp_execViews @testId, @testRunId

	DECLARE @endAt datetime2
	SET @endAt = (SELECT CURRENT_TIMESTAMP)

	UPDATE TestRuns
	SET EndAt = @endAt
	WHERE TestRunID = @testRunId

GO

SELECT *
FROM TABLES
SELECT * FROM TestTables
SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews



EXEC usp_testRun 'test1'
EXEC usp_testRun 'test2'
EXEC usp_testRun 'test3'


EXEC usp_addANewTest 'test1', 'Performs_on,Performers,Song,Album', 'view_getAllSongs,view_getPerformersAndAlbumsWithSongs,view_getAlbumNameAndPercentageOfAddedSongs', 50
EXEC usp_addANewTest 'test2', 'Performs_on,Performers,Song,Album', 'view_getAllSongs,view_getPerformersAndAlbumsWithSongs,view_getAlbumNameAndPercentageOfAddedSongs', 100
EXEC usp_addANewTest 'test3', 'Performs_on,Performers,Song,Album', 'view_getAllSongs,view_getPerformersAndAlbumsWithSongs,view_getAlbumNameAndPercentageOfAddedSongs', 500


--- the position will be 1 for the table that must be deleted first and n for the table that must be deleted last, so we will take the position ascendingly when deleting the data
--- and we will get the positions descendingly when inserting data 
--- 1. run a test( only the test name as a parameter) -> TestRuns
---					before everything, get the id of the test corresponding to that name and also save the current time( in StartAt) -----> done
---					a. delete from all the tables in that test name( give testId as parameter)
---										initially, save the current time( in StartAt)
---										take every table from Tables using TestTables and testId and delete the data from it, be careful with the position!!!
---										use cursor
---										in the select user ORDER BY to sort them according to the position
---										finally, save the current time(in EndsAt)
---					b. insert for all the table in that test name( give testId as parameter)
---										initially, save the current time( in StartAt)
---										take every table from Tables using TestTables and testId and insert data to it, be careful with the position and the number of rows that are to be added
---										how to insert data: use rand() and check the type to see what you should do
---											First case: table with a single column primary key and no foreign keys, here I simply add values to the pther columns since the primary key is identity
---											We should see which column is the primary key and check if it is identity, put as primary key the current row otherwise( primary ley and no identity)
---											for int, used rand, for nvarchar use "random string #[no of string]"
---											Second case: table with a single-column primary key and at least one foreign key
---											Third case: table with multi-column primary key
---										use cursor
---										finally, save the current time(in EndsAt)				
---					c. exec the views( give testId as parameter)
---										initially, save the current time( in StartAt)
---										take every view from Views using TestViews and testId and exec it
---										finally, save the current time(in EndsAt)
---					after everything, save the current time( in EndsAt) -----> done
--- 2. add a new test -> Tests( testName, tables and views)
---									we will randomly choose the number of rows using rand
---									the tables are in the order of their position
---									declare a variable named position and set it to 1
---						a. insert the test name in the Tests table also get the testId
---						b. check if the table is already added, if it is added get the tableId, otherwise insert it and also get the tableId
---						c. using the tableId and the testId, add a new value in the TestTables table, generate randomly the no of rows and set the position to the current position and increment it
---						d. check if the view is already added, if it is added get the viewId, otherwise insert it and also get the viewId
---						e. using the tableId and the viewId add a new value in the TestViews table
--- b and c are in a cursor and d and e are in another cursor
--- b and c will be in a method and d and e will be in another one

SELECT * FROM sys.columns

--- the column name and the type --- 
SELECT col.name, typ.name, col.is_identity
	FROM sys.columns AS col
	INNER JOIN sys.tables AS tab ON tab.object_id = col.object_id
	INNER JOIN sys.types AS typ ON typ.system_type_id = col.system_type_id
	WHERE tab.name = N'Song'


--- to get the foreign keys of a table ---
SELECT
    tab1.name AS [table],
    col1.name AS [column]
FROM sys.foreign_key_columns fkc
INNER JOIN sys.objects obj
    ON obj.object_id = fkc.constraint_object_id
INNER JOIN sys.tables tab1
    ON tab1.object_id = fkc.parent_object_id
INNER JOIN sys.columns col1
    ON col1.column_id = parent_column_id AND col1.object_id = tab1.object_id

	

	select * from Song
	select * from Performs_on
	select * from Performers
	SELECT * FROM ALBUM
	

	
	

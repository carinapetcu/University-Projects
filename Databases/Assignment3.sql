-------------------------- ASSIGNMENT 3 --------------------------

--------1. Write SQL scripts that(and their reverse):
----a. Modify the type of a column Version1 
ALTER PROCEDURE uspModifyTypeOfColumn
AS
	ALTER TABLE Streaming_platform
	ALTER COLUMN number_of_streams TINYINT
GO

EXEC uspModifyTypeOfColumn

ALTER PROCEDURE uspModifyTypeOfColumnReverse
AS
	ALTER TABLE	Streaming_platform
	ALTER COLUMN number_of_streams INT
GO

EXEC uspModifyTypeOfColumnReverse

----b. Add/ remove a column Version2
ALTER PROCEDURE uspAddColumn
AS
	ALTER TABLE Streaming_platform
	ADD paid_or_free VARCHAR(10)
GO

EXEC uspAddColumn

ALTER PROCEDURE uspAddColumnReverse
AS
	ALTER TABLE Streaming_platform
	DROP COLUMN paid_or_free
GO


EXEC uspAddColumnReverse

----c. Add/ remove a DEFAULT constraint Version3
ALTER PROCEDURE uspAddDefaultConstraint
AS
	ALTER TABLE Streaming_platform
	ADD CONSTRAINT df_number_of_streams 
	DEFAULT 0 FOR number_of_streams
GO

EXEC uspAddDefaultConstraint

ALTER PROCEDURE uspAddDefaultConstraintReverse
AS
	ALTER TABLE Streaming_platform
	DROP CONSTRAINT df_number_of_streams
GO

EXEC uspAddDefaultConstraintReverse


----d. Add/remove a primary key Version4
ALTER PROCEDURE uspRemovePrimaryKey
AS
	ALTER TABLE Is_of
	DROP CONSTRAINT PK__Is_of
GO

EXEC uspRemovePrimaryKey

ALTER PROCEDURE uspRemovePrimaryKeyReverse
AS
	ALTER TABLE Is_of
	ADD CONSTRAINT PK__Is_of PRIMARY KEY (sid, gid);
GO

EXEC uspRemovePrimaryKeyReverse

----e. Add/remove a candidate key Version5
ALTER PROCEDURE uspRemoveCandidateKey
AS	
	ALTER TABLE Label_company
	DROP CONSTRAINT UQ_Name
GO

EXEC uspRemoveCandidateKey

ALTER PROCEDURE uspRemoveCandidateKeyReverse
AS 
	ALTER TABLE Label_company
	ADD CONSTRAINT UQ_Name UNIQUE(lcname)
GO

EXEC uspRemoveCandidateKeyReverse


----f.Add/remove a foreign key Version6
ALTER PROCEDURE uspRemoveForeignKey
AS
	ALTER TABLE Performers
	DROP CONSTRAINT FK__Performers__lcid
GO

EXEC uspRemoveForeignKey

ALTER PROCEDURE uspRemoveForeignKeyReverse
AS
	ALTER TABLE Performers
	ADD CONSTRAINT FK__Performers__lcid FOREIGN KEY(lcid) REFERENCES Label_company(lcid)
GO

EXEC uspRemoveForeignKeyReverse

----g. Create/drop a table Version7
ALTER PROCEDURE uspCreateNewTable
AS
	CREATE TABLE Country(
		cid INT IDENTITY(1,1) PRIMARY KEY,
		name VARCHAR(50))
GO

EXEC uspCreateNewTable

ALTER PROCEDURE uspCreateNewTableReverse
AS
	DROP TABLE Country
GO

EXEC uspCreateNewTableReverse

---- create table version -----
CREATE TABLE Version
( version INT PRIMARY KEY
)

INSERT INTO Version(version) VALUES (0)

SELECT * 
FROM Version

---- create table ChangesDones ----

CREATE TABLE ChangesDone(
version INT IDENTITY(1,1) PRIMARY KEY,
usp VARCHAR(50),
uspReverse VARCHAR(50)
)

DROP TABLE ChangesDone

SELECT *
FROM ChangesDone

CREATE PROCEDURE incrementVersion
AS
	DECLARE @version INT
	SET @version = (SELECT version
					FROM Version)
	SET @version = @version + 1
	EXEC updateVersion @version
GO

CREATE PROCEDURE updateVersion (@version INT)
AS
	UPDATE Version
	SET version = @version
GO

CREATE PROCEDURE updateChangesDone (@usp VARCHAR(50), @uspReverse VARCHAR(50))
AS
	INSERT INTO ChangesDone(usp, uspReverse) VALUES (@usp, @uspReverse)
GO

ALTER PROCEDURE bringDatabaseToVersion @version INT
AS
	DECLARE @currentVersion INT
	SET @currentVersion = (SELECT version
							FROM Version)
	IF(@currentVersion > @version)
		WHILE (@currentVersion > @version)
		BEGIN
			DECLARE @commandReverse VARCHAR(50)
			SET @commandReverse = (SELECT uspReverse
					FROM ChangesDone
					WHERE version = @currentVersion)
			EXEC @commandReverse
			SET @currentVersion = @currentVersion - 1
		END
	ELSE IF(@currentVersion < @version)
		WHILE(@currentVersion < @version)
		BEGIN
			SET @currentVersion = @currentVersion + 1
			DECLARE @command VARCHAR(50)
			SET @command = (SELECT usp
					FROM ChangesDone
					WHERE version = @currentVersion)
			EXEC @command
		END
	EXEC updateVersion @currentVersion
GO

DROP PROCEDURE bringDatabaseToVersion

EXEC updateVersion 0

EXEC bringDatabaseToVersion 6

 EXEC updateChangesDone 'uspModifyTypeOfColumn', 'uspModifyTypeOfColumnReverse' 
 EXEC updateChangesDone 'uspAddColumn', 'uspAddColumnReverse' 
 EXEC updateChangesDone 'uspAddDefaultConstraint', 'uspAddDefaultConstraintReverse' 
 EXEC updateChangesDone 'uspRemovePrimaryKey', 'uspRemovePrimaryKeyReverse' 
 EXEC updateChangesDone 'uspRemoveCandidateKey', 'uspRemoveCandidateKeyReverse' 
 EXEC updateChangesDone 'uspRemoveForeignKey', 'uspRemoveForeignKeyReverse' 
 EXEC updateChangesDone 'uspCreateNewTable', 'uspCreateNewTableReverse' 

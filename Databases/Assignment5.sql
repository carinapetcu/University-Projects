-------------------------------------- Assignment 5 ----------------------------------------

---- I will create the 3 required tables first
CREATE TABLE Ta(
	aid INT PRIMARY KEY IDENTITY(1,1),
	a2 INT UNIQUE,
	a3 INT
)

CREATE TABLE Tb(
	bid INT PRIMARY KEY IDENTITY(1,1),
	b2 INT	
)

CREATE TABLE Tc(
	cid INT PRIMARY KEY IDENTITY(1,1),
	aid INT REFERENCES Ta(aid),
	bid INT REFERENCES Tb(bid)
)

-- clustered index scan
SELECT *
FROM Tc 
WHERE tc.aid > 101

-- clustered index seek
SELECT b2 
FROM Tb 
WHERE bid = 100

-- nonclustered index scan
SELECT a2
FROM Ta

-- nonclustered index seek
SELECT aid
FROM Ta
WHERE Ta.a2 > 500

-- key lookup (+ nonclustered index seek(on a2))
SELECT *
FROM Ta
WHERE Ta.a2 = 238


--  Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan.
IF EXISTS(SELECT * FROM sys.indexes WHERE NAME = 'index_nonclustered_b2')
	DROP INDEX index_nonclustered_b2 ON TB
SELECT *
FROM Tb
WHERE b2 = 562 -- clustered index scan, estimated I/O cost = 0.0083102, estimated operator cost = 0.0106672, estimated CPU cost = 0.002357, estimated subtree cost = 0.0106672


-- Create a nonclustered index that can speed up the query.
CREATE NONCLUSTERED INDEX index_nonclustered_b2 ON Tb(b2)
SELECT *
FROM Tb
WHERE b2 = 562 -- nonclustered index seek, estimated I/O cost = 0.003125, estimated operator cost = 0.0032832, estimated CPU cost = 0.0001582, estimated subtree cost = 0.0032832


-- Create a view that joins at least 2 tables
CREATE OR ALTER VIEW view_joinTables 
AS
	SELECT Tc.bid, Tc.cid
	FROM Tc
	INNER JOIN Tb ON Tb.bid = Tc.bid
	WHERE Tc.bid > 100 AND Tc.bid < 1300
GO

-- Check whether existing indexes are helpful
IF EXISTS(SELECT * 
FROM sys.indexes I
INNER JOIN sys.objects O ON I.object_id = O.object_id
WHERE I.name = 'index_nonclustered_bid' AND O.name = 'Tc')
DROP INDEX index_nonclustered_bid ON Tc
SELECT * FROM view_joinTables   -- clustered index seek( Tb, bid being PK), estimated I/O cost = 0.0046065, estimated operator cost = 0.0060824, estimated CPU cost = 0.0014759, estimated subtree cost = 0.0060824
								-- clustered index scan( Tc, cid being PK), estimated I/O cost = 0.0068287, estimated operator cost = 0.0091857, estimated CPU cost = 0.002357, estimated subtree cost = 0.0091857

-- Create index
CREATE NONCLUSTERED INDEX index_nonclustered_bid ON Tc(bid) 
SELECT * FROM view_joinTables   -- clustered index seek( Tb, bid being PK), estimated I/O cost = 0.0046065, estimated operator cost = 0.0060824, estimated CPU cost = 0.0014759, estimated subtree cost = 0.0060824
								-- nonclustered index seek( Tc, cid being PK), estimated I/O cost = 0.0046065, estimated operator cost = 0.0060824, estimated CPU cost = 0.0014759, estimated subtree cost = 0.0060824

EXEC sp_helpindex Ta
EXEC sp_helpindex Tb
EXEC sp_helpindex Tc

usp_insertRowsInTableTa 'Ta', 2000
usp_insertRowsInTable 'Tb', 2000
usp_insertRowsInTable 'Tc', 2000

select count(*) from Tc

drop table Ta
drop table Tb
drop table Tc

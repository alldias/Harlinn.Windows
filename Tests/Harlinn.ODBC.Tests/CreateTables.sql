/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

CREATE TABLE dbo.TimeseriesValue1
(
	Id bigint NOT NULL,
	Ts datetime2(7) NOT NULL,
	Flags int NOT NULL,
	val double precision NOT NULL,
	CONSTRAINT PK_TSV1 PRIMARY KEY(ID,Ts)
); 
go 

INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 1, '2021-01-01 00:00:01.0000001', 0, 1.0 )
go
INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 1, '2021-01-01 00:00:02.0000001', 0, 2.0 )
go
INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 1, '2021-01-01 00:00:03.0000001', 0, 3.0 )
go

INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 2, '2021-01-01 00:00:01.0000002', 0, 1.0 )
go
INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 2, '2021-01-01 00:00:02.0000002', 0, 2.0 )
go
INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 2, '2021-01-01 00:00:03.0000002', 0, 3.0 )
go


CREATE TABLE dbo.TimeseriesValue2
(
	Id bigint NOT NULL,
	Ts bigint NOT NULL,
	Flags int NOT NULL,
	val double precision NOT NULL,
	CONSTRAINT PK_TSV2 PRIMARY KEY(ID,Ts)
); 
go 


CREATE TABLE [dbo].[Track]
(
	[Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
	[OptimisticLockField] [int] NOT NULL,
	[Tracker] [uniqueidentifier] NOT NULL,
	[TrackNumber] [bigint] NOT NULL,
	[Timestamp] [bigint] NOT NULL,
    CONSTRAINT [PK_Track] PRIMARY KEY([Id] ),
	CONSTRAINT [UNQ_Track_TrackNumber_Timestamp] UNIQUE ([Tracker],[TrackNumber],[Timestamp])
 );
go

CREATE TABLE [dbo].[TrackValues]
(
	[Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
	[OptimisticLockField] [int] NOT NULL,
	[Track] [uniqueidentifier] NOT NULL,
	[Timestamp] [bigint] NOT NULL,
	[Flags] [int] NOT NULL,
	[Status] [int] NOT NULL,
	[Latitude] [float] NOT NULL,
	[Longitude] [float] NOT NULL,
	[Speed] [float] NOT NULL,
	[Course] [float] NOT NULL,
	[Heading] [float] NOT NULL,
	CONSTRAINT [PK_dbo.TrackValues] PRIMARY KEY ( [Id] ),
	CONSTRAINT [UNQ_TrackValue_Track_Timestamp] UNIQUE ([Track],[Timestamp]),
	CONSTRAINT [FK_TrackValue_Track] FOREIGN KEY([Track]) REFERENCES [dbo].[Track] ([Id])
);
GO

CREATE OR ALTER VIEW TrackViewEx
AS
  SELECT 
     t1.[Id]
    ,t1.[OptimisticLockField]
    ,t1.[Tracker]
    ,t1.[TrackNumber]
    ,ISNULL((SELECT MAX( tv.[Timestamp] ) FROM [dbo].[TrackValues] tv WHERE tv.Track = t1.Id ), t1.[Timestamp]) As [Timestamp]
FROM [dbo].[Track] t1
GO 

PRAGMA foreign_keys = ON;
PRAGMA table_info(Users);

-- Drop existing tables
DROP TABLE IF EXISTS ServiceLogs;
DROP TABLE IF EXISTS Reports;
DROP TABLE IF EXISTS Users;
DROP TABLE IF EXISTS Members;
DROP TABLE IF EXISTS Services;

-- Create Users table (only for system users)
CREATE TABLE IF NOT EXISTS Users (
    user_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    address TEXT NOT NULL,
    city TEXT NOT NULL,
    state TEXT NOT NULL,
    zip_code TEXT NOT NULL,
    user_type TEXT CHECK(user_type IN ('Provider', 'Operator', 'Manager')) NOT NULL
);

-- Create Members table (completely separate)
CREATE TABLE Members (
    member_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    address TEXT NOT NULL,
    city TEXT NOT NULL,
    state TEXT NOT NULL,
    zip_code TEXT NOT NULL,
    status TEXT NOT NULL CHECK (status IN ('Active', 'Suspended'))
);

-- Create Services table
CREATE TABLE Services (
    service_code TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    fee REAL NOT NULL CHECK (fee >= 0)
);

-- Create ServiceLogs table
CREATE TABLE ServiceLogs (
    log_id INTEGER PRIMARY KEY AUTOINCREMENT,
    date_of_service TEXT NOT NULL,
    timestamp_recorded TEXT NOT NULL,
    provider_id INTEGER NOT NULL, -- Referrences Users(user_id)
    member_id INTEGER NOT NULL,
    service_code TEXT NOT NULL, -- changed from Integer to Text
    comments TEXT,
    FOREIGN KEY (provider_id) REFERENCES Users(user_id),
    FOREIGN KEY (member_id) REFERENCES Members(member_id),
    FOREIGN KEY (service_code) REFERENCES Services(service_code)
);

-- Create Reports table
CREATE TABLE Reports (
    report_id INTEGER PRIMARY KEY AUTOINCREMENT,
    report_type TEXT NOT NULL CHECK (report_type IN ('Member', 'Provider', 'Summary', 'EFT')),
    generated_date TEXT NOT NULL,
    content TEXT NOT NULL
);

-- VIEW: Member Report View
DROP VIEW IF EXISTS MemberReportView;
CREATE VIEW IF NOT EXISTS MemberReportView AS
SELECT
    m.member_id AS ID,
    m.name AS MemberName,
    m.address AS MemberAddress,
    m.city AS City,
    m.state AS State,
    m.zip_code AS Zipcode,
    sl.date_of_service AS DateOfService,
    p.name AS ProviderName,
    s.name AS ServiceName
FROM ServiceLogs AS sl
    JOIN Members m ON sl.member_id = m.member_id
    JOIN Users p ON sl.provider_id = p.user_id
    JOIN Services s ON sl.service_code = s.service_code
WHERE p.user_type = 'Provider'
ORDER BY m.member_id;


--VIEW: Provider Report View
DROP VIEW IF EXISTS ProviderReportView;
CREATE VIEW ProviderReportView AS
SELECT 
    s.date_of_service AS DateOfService,
    s.timestamp_recorded AS TimeStamp, 
    m.name AS MemberName,
    m.member_id AS MemberID,
    s.service_code AS ServiceCode, 
    sv.fee AS ServiceFee,
    s.provider_id AS ProviderID,
    u.user_type
FROM ServiceLogs s
JOIN Members m ON s.member_id = m.member_id
JOIN Services sv ON s.service_code = sv.service_code
JOIN Users u ON s.provider_id = u.user_id
WHERE u.user_type = 'Provider'
ORDER BY s.date_of_service;


--VIEW: Summary Report View

DROP VIEW IF EXISTS SummaryReportView;

CREATE VIEW SummaryReportView AS
SELECT
    u.name AS ProviderName,
    u.user_id AS ProviderID,
    COUNT(s.service_code) AS NumConsultations,
    SUM(sv.fee) AS TotalFee,
    s.date_of_service AS DateOfService
    --s.date_of_service) AS LastServiceDate
FROM ServiceLogs s
JOIN Users u ON s.provider_id = u.user_id
JOIN Services sv ON s.service_code = sv.service_code
--WHERE u.user_type = 'Provider'
GROUP BY u.user_id;
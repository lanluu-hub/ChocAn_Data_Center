PRAGMA foreign_keys = ON;

-- Drop existing tables for clean development setup
DROP TABLE IF EXISTS ServiceLogs;
DROP TABLE IF EXISTS Reports;
DROP TABLE IF EXISTS Members;
DROP TABLE IF EXISTS Providers;
DROP TABLE IF EXISTS Operators;
DROP TABLE IF EXISTS Services;

-- Create Members table
CREATE TABLE Members (
    member_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    address TEXT NOT NULL,
    city TEXT NOT NULL,
    state TEXT NOT NULL,
    zip_code TEXT NOT NULL,
    status TEXT NOT NULL CHECK (status IN ('Active', 'Suspended'))
);

-- Create Providers table
CREATE TABLE Providers (
    provider_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    address TEXT NOT NULL,
    city TEXT NOT NULL,
    state TEXT NOT NULL,
    zip_code TEXT NOT NULL
);

-- Create Operators table
CREATE TABLE Operators (
    operator_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    address TEXT NOT NULL,
    city TEXT NOT NULL,
    state TEXT NOT NULL,
    zip_code TEXT NOT NULL
);

-- Create Services table
CREATE TABLE Services (
    service_code INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    fee REAL NOT NULL CHECK (fee >= 0)
);

-- Create ServiceLogs table
CREATE TABLE ServiceLogs (
    log_id INTEGER PRIMARY KEY AUTOINCREMENT,
    date_of_service TEXT NOT NULL,
    timestamp_recorded TEXT NOT NULL,
    provider_id INTEGER NOT NULL,
    member_id INTEGER NOT NULL,
    service_code INTEGER NOT NULL,
    comments TEXT,
    FOREIGN KEY (provider_id) REFERENCES Providers(provider_id),
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

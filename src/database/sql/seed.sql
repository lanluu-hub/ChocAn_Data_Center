-- Insert Members (standalone)
INSERT INTO Members (member_id, name, address, city, state, zip_code, status) VALUES
(100000001, 'Son Phan', 'CS314 St', 'Whitespace', 'OR', '97201', 'Active'),
(100000002, 'Lan Luu', 'CS314 St', 'Whitespace', 'OR', '97201', 'Active'),
(100000003, 'Tin Duong', 'CS314 St', 'Portland', 'OR', '97201', 'Active'),
(100000004, 'Hunter Gambee-Iddings', 'CS314 St', 'Whitespace', 'OR', '97201', 'Active'),
(100000005, 'Piper Lake', 'CS314 St', 'Whitespace', 'OR', '97201', 'Active'),
(100000006, 'Teacher', 'CS314 St', 'Portland', 'OR', '97201', 'Suspended'),
(100000007, 'Alex Kim', '777 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000008, 'Bella Tran', '778 Maple Ave', 'Portland', 'OR', '97202', 'Suspended'),
(100000009, 'Chris Lee', '779 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000010, 'Dana Wu', '780 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000011, 'Ethan Park', '781 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000012, 'Fiona Lin', '782 Maple Ave', 'Portland', 'OR', '97202', 'Suspended'),
(100000013, 'George Chen', '783 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000014, 'Hannah Nguyen', '784 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000015, 'Isaac Brown', '785 Maple Ave', 'Portland', 'OR', '97202', 'Suspended'),
(100000016, 'Jasmine Moore', '786 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000017, 'Kyle Smith', '787 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000018, 'Lara White', '788 Maple Ave', 'Portland', 'OR', '97202', 'Suspended'),
(100000019, 'Mason Gray', '789 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000020, 'Nina Davis', '790 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000021, 'Owen Harris', '791 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000022, 'Paula Brooks', '792 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000023, 'Quinn Foster', '793 Maple Ave', 'Portland', 'OR', '97202', 'Suspended'),
(100000024, 'Riley Adams', '794 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000025, 'Sophie Clark', '795 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000026, 'Tyler Hall', '796 Maple Ave', 'Portland', 'OR', '97202', 'Suspended'),
(100000027, 'Uma Robinson', '797 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000028, 'Victor Young', '798 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000029, 'Wendy Scott', '799 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000030, 'Xavier Price', '800 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000031, 'Yara Cox', '801 Maple Ave', 'Portland', 'OR', '97202', 'Suspended'),
(100000032, 'Zane Bell', '802 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000033, 'Aaron Reed', '803 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000034, 'Bianca Ford', '804 Maple Ave', 'Portland', 'OR', '97202', 'Active'),
(100000035, 'Caleb Simmons', '805 Maple Ave', 'Portland', 'OR', '97202', 'Suspended'),
(100000036, 'Diana Hayes', '806 Maple Ave', 'Portland', 'OR', '97202', 'Active');



-- Insert Users (only system users)
INSERT INTO Users (user_id, name, address, city, state, zip_code, user_type) VALUES
-- Providers
(200000001, 'user1', 'CS314 St', 'Whitespace', 'OR', '97201', 'Provider'),
(200000002, 'user2', 'CS314 St', 'Whitespace', 'OR', '97201', 'Provider'),

-- Operators
(300000001, 'operator1', 'CS314 St', 'Whitespace', 'OR', '97201', 'Operator'),

-- Managers
(400000001, 'manager1', 'CS314 St', 'Whitespace', 'OR', '97201', 'Manager');

-- Seed 30 Services
INSERT INTO Services (service_code, name, fee) VALUES
(100001, 'Emergency Room Visit', 250.00),
(100002, 'Inpatient Consultation', 180.00),
(100003, 'Outpatient Follow-Up', 95.00),
(100004, 'MRI Scan', 600.00),
(100005, 'Physical Therapy Session', 85.00),
(100006, 'X-Ray Diagnostic', 120.00),
(100007, 'Blood Test Panel', 60.00),
(100008, 'Vaccination (General)', 35.00),
(100009, 'Cardiology Checkup', 210.00),
(100010, 'Mental Health Counseling', 150.00),
(100011, 'Dermatology Visit', 125.00),
(100012, 'Prenatal Checkup', 100.00),
(100013, 'Pediatric Exam', 90.00),
(100014, 'ENT Consultation', 130.00),
(100015, 'Nutrition Counseling', 70.00),
(100016, 'Chiropractic Adjustment', 65.00),
(100017, 'Vision Screening', 45.00),
(100018, 'Dental Cleaning', 110.00),
(100019, 'Oral Surgery Evaluation', 180.00),
(100020, 'Gastroenterology Visit', 195.00),
(100021, 'Orthopedic Assessment', 175.00),
(100022, 'Neurological Exam', 220.00),
(100023, 'Urinalysis', 50.00),
(100024, 'Allergy Testing', 145.00),
(100025, 'COVID-19 Test', 40.00),
(100026, 'Hearing Test', 55.00),
(100027, 'Stress Test (Cardio)', 250.00),
(100028, 'Smoking Cessation Program', 90.00),
(100029, 'Wellness Coaching', 75.00),
(100030, 'Diabetes Management Session', 105.00);


-- ServiceLog Dummy Data --- 

INSERT INTO ServiceLogs (
    date_of_service, timestamp_recorded,
    provider_id, member_id, service_code, comments
) VALUES
('05-25-2025', '05-25-2025 14:35:00', 200000001, 100000001, 100001, 'Routine checkup'),
('05-25-2025', '05-25-2025 14:40:00', 200000001, 100000002, 100002, 'First visit'),
('05-26-2025', '05-26-2025 10:00:00', 200000002, 100000004, 100004, 'Follow-up'),
('05-26-2025', '05-26-2025 11:30:00', 200000002, 100000005, 100003, 'Consultation'),
('05-26-2025', '05-26-2025 13:00:00', 200000001, 100000006, 100006, 'Back pain treatment'),
('05-27-2025', '05-27-2025 09:15:00', 200000003, 100000007, 100005, 'Routine X-ray'),
('05-27-2025', '05-27-2025 09:45:00', 200000001, 100000008, 100007, 'Vaccination'),
('05-27-2025', '05-27-2025 10:30:00', 200000001, 100000009, 100008, 'Heart checkup'),
('05-28-2025', '05-28-2025 08:00:00', 200000002, 100000010, 100010, 'Dental cleaning'),
('05-28-2025', '05-28-2025 08:45:00', 200000003, 100000011, 100009, 'Therapy session');
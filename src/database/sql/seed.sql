-- Insert sample Members
INSERT INTO Members (member_id, name, address, city, state, zip_code, status) VALUES
(100000001, 'Alice Choco', '123 Sweet St', 'Portland', 'OR', '97201', 'Active'),
(100000002, 'Bob Cocoa', '124 Sweet St', 'Portland', 'OR', '97201', 'Active'),
(100000003, 'Charlie Dark', '125 Sweet St', 'Portland', 'OR', '97201', 'Suspended');

-- Insert sample Providers
INSERT INTO Providers (provider_id, name, address, city, state, zip_code) VALUES
(200000001, 'Dr. Cocoa Bean', '456 Bitter Blvd', 'Portland', 'OR', '97202'),
(200000002, 'Dr. Dark Chocolate', '789 Sweet St', 'Portland', 'OR', '97203');

-- Insert sample Operators
INSERT INTO Operators (operator_id, name, address, city, state, zip_code) VALUES
(300000001, 'Operator One', '100 Admin Rd', 'Portland', 'OR', '97204');

-- Seed 30 Services
INSERT INTO Services (service_code, name, fee) VALUES
('HS001', 'Emergency Room Visit', 250.00),
('HS002', 'Inpatient Consultation', 180.00),
('HS003', 'Outpatient Follow-Up', 95.00),
('HS004', 'MRI Scan', 600.00),
('HS005', 'Physical Therapy Session', 85.00),
('HS006', 'X-Ray Diagnostic', 120.00),
('HS007', 'Blood Test Panel', 60.00),
('HS008', 'Vaccination (General)', 35.00),
('HS009', 'Cardiology Checkup', 210.00),
('HS010', 'Mental Health Counseling', 150.00),
('HS011', 'Dermatology Visit', 125.00),
('HS012', 'Prenatal Checkup', 100.00),
('HS013', 'Pediatric Exam', 90.00),
('HS014', 'ENT Consultation', 130.00),
('HS015', 'Nutrition Counseling', 70.00),
('HS016', 'Chiropractic Adjustment', 65.00),
('HS017', 'Vision Screening', 45.00),
('HS018', 'Dental Cleaning', 110.00),
('HS019', 'Oral Surgery Evaluation', 180.00),
('HS020', 'Gastroenterology Visit', 195.00),
('HS021', 'Orthopedic Assessment', 175.00),
('HS022', 'Neurological Exam', 220.00),
('HS023', 'Urinalysis', 50.00),
('HS024', 'Allergy Testing', 145.00),
('HS025', 'COVID-19 Test', 40.00),
('HS026', 'Hearing Test', 55.00),
('HS027', 'Stress Test (Cardio)', 250.00),
('HS028', 'Smoking Cessation Program', 90.00),
('HS029', 'Wellness Coaching', 75.00),
('HS030', 'Diabetes Management Session', 105.00);

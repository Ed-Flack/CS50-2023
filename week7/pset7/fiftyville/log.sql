-- Keep a log of any SQL queries you execute as you solve the mystery.

--  All I know to start is that the theft took place on July 28, 2021 on Humphrey Street, so checking crime_scene_reports for info.
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- The crime related to the theft of the CS50 duck has id 295. It happened at 10:15am at Humphrey Street bakery, 3 witnesses were interviewed.
-- Checking interviews on that day.
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

-- A witness said within 10 minutes of the theft, a thief got into a car a drove off.
-- Another witness said he saw the theif withdraw money from the ATM on Leggett Street.
-- Another witness said when the thief was leaving the bakery, they called someone and spoke to them for less then a minute.
-- In the call they mentioned they were planning the earliest flight out of Fiftyville the next day.
-- The person on the other end of the phone was asked to purchase the flight ticket.

-- Checking bakery_security_logs at the time of the crime.
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 0 and minute <= 25;

-- Licence plates of those who exited within 10 minutes of the crime are 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55.

-- Checking atm_transations
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Account numbers who withdrew on Legget Street that day are 28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199.

-- Checking the flight
SELECT * FROM FLIGHTS WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute;

-- Earliest flight has id 36, flying from origin aiport 8 to destination airport 4.

-- Checking where the destination airport is.
SELECT * FROM airports WHERE ID = 4;

-- This airport is in New York City. This means the thief escaped there.

-- Checking passengers of flight
SELECT name, license_plate FROM people, passengers WHERE people.passport_number = passengers.passport_number AND flight_id = 36;

-- Checking if license_plate of passengers on flight matches any of the liceneses that left the bakery.
SELECT name, people.license_plate FROM people, passengers WHERE people.passport_number = passengers.passport_number
AND flight_id = 36 AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 0 and minute <= 25 AND activity = 'exit');

-- Found 4 matches: Sofia, Bruce, Kelsey, and Luca, with license plates G412CB7, 94KL13X, 0NTHK55, 4328GD8 respectively.

-- Checking if any of those people withdrew from the ATM on Legget Street.
SELECT people.id, name FROM people, passengers, bank_accounts WHERE people.passport_number = passengers.passport_number
AND flight_id = 36 AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 0 and minute <= 25 AND activity = 'exit')
AND bank_accounts.person_id = people.id and account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021
    AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

-- Found 2 matches: Bruce (id 686048), and Luca (id 467400).

-- Checking if Bruce or Luca made any calls on that day for less than a minute (presumiung the duration is in seconds).
SELECT * FROM people, phone_calls WHERE (people.id = 686048 OR people.id = 467400) AND people.phone_number = phone_calls.caller
AND year = 2021 AND month = 7 AND day = 28 AND duration <= 60;

-- Found one match: Bruce. This means Bruce is the thief.
-- Bruce's passport number is 5773159633.
-- Bruce called (375) 555-8161.

-- Checking people with the number (375) 555-8161.
SELECT * FROM people WHERE phone_number = '(375) 555-8161';

-- Found one match: Robin. This means Robin is the accomplice.

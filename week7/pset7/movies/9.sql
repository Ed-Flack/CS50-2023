SELECT DISTINCT(name) FROM people, stars, movies
WHERE people.id = person_id
AND movie_id = movies.id
AND year = 2004
ORDER BY birth;

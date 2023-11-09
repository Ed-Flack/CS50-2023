SELECT name FROM people, stars, movies
WHERE people.id = person_id
AND movie_id = movies.id
AND title = 'Toy Story';

# Lab 8: Trivia

You are welcome to collaborate with one or two classmates on this lab, though it is expected that every student in any such group contribute equally to the lab.

Write a webpage that lets users answer trivia questions.

![screenshot of trivia questions](https://github.com/Ed-Flack/CS50-2023/assets/44028291/8132b304-5f0f-440c-82f3-52ac4151876b)

## Implementation Details

Design a webpage using HTML, CSS, and JavaScript to let users answer trivia questions.

*   In `index.html`, add beneath “Part 1” a multiple-choice trivia question of your choosing with HTML.
    *   You should use an `h3` heading for the text of your question.
    *   You should have one `button` for each of the possible answer choices. There should be at least three answer choices, of which exactly one should be correct.
*   Using JavaScript, add logic so that the buttons change colors when a user clicks on them.
    *   If a user clicks on a button with an incorrect answer, the button should turn red and text should appear beneath the question that says “Incorrect”.
    *   If a user clicks on a button with the correct answer, the button should turn green and text should appear beneath the question that says “Correct!”.
*   In `index.html`, add beneath “Part 2” a text-based free response question of your choosing with HTML.
    *   You should use an `h3` heading for the text of your question.
    *   You should use an `input` field to let the user type a response.
    *   You should use a `button` to let the user confirm their answer.
*   Using JavaScript, add logic so that the text field changes color when a user confirms their answer.
    *   If the user types an incorrect answer and presses the confirmation button, the text field should turn red and text should appear beneath the question that says “Incorrect”.
    *   If the user types the correct answer and presses the confirmation button, the input field should turn green and text should appear beneath the question that says “Correct!”.

Optionally, you may also:

*   Edit `styles.css` to change the CSS of your webpage!
*   Add additional trivia questions to your trivia quiz if you would like!

## Hints

*   Use [`document.querySelector`](https://developer.mozilla.org/en-US/docs/Web/API/Document/querySelector) to query for a single HTML element.
*   Use [`document.querySelectorAll`](https://developer.mozilla.org/en-US/docs/Web/API/Document/querySelectorAll) to query for multiple HTML elements that match a query. The function returns an array of all matching elements.


## Testing

But be sure to test both incorrect and correct responses for each of your questions to ensure that your webpage responds appropriately.

Run `http-server` in your terminal while in your `lab8` directory to start a web server that serves your webpage.

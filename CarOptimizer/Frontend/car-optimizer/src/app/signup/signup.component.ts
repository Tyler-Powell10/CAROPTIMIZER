import { Component } from '@angular/core';
import { AuthService } from '../services/auth.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.css']
})
export class SignupComponent {
  fullName: string = '';
  email: string = '';
  password: string = '';
  confirmPassword: string = '';

  constructor(private authService: AuthService, private router: Router) { }

  onSignup() {
    if (this.password === this.confirmPassword) {
      const signupData = {
        fullName: this.fullName,
        email: this.email,
        password: this.password
      };

      console.log('Attempting to sign up with data:', signupData);

      this.authService.signup(signupData)
        .subscribe({
          next: (response) => {
            console.log('User registered successfully', response);
            this.router.navigateByUrl('/login');
          },
          error: (error) => {
            console.error('Registration failed', error);
            //! show password inefficience etc 
          }
        });
    } else {
      console.error('Passwords do not match');
      //! show passwords dont match
    }
  }
}

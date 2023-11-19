import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from '../services/auth.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})

export class LoginComponent {
  user = { email: '', password: '' };
  isLoggedIn = false;

  constructor(private authService: AuthService, private router: Router) {}

  onLogin() {
    this.authService.login(this.user).subscribe(response => {
      this.isLoggedIn = true;
      this.router.navigate(['/home']);
      console.log("login success")
    }, error => {
      console.error(error);
    });
  }
}
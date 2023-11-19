import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private signupUrl = 'http://localhost:8080/signup';
  private loginUrl = 'http://localhost:8080/login';

  constructor(private http: HttpClient) {}

  login(user: { email: string, password: string }): Observable<any> {
    const payload = {
      username: user.email,
      password: user.password
    };

    console.log('Sending login request with payload:', payload);

    return this.http.post(this.loginUrl, payload);
  }

  signup(user: { fullName: string, email: string, password: string }): Observable<any> {
    const payload = {
      username: user.email, 
      name_user: user.fullName,
      password: user.password
    };

    console.log('Sending signup request with payload:', payload);

    return this.http.post(this.signupUrl, payload);
  }
}

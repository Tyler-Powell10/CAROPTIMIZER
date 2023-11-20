import { Injectable } from '@angular/core';
import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { Observable, catchError, throwError } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private signupUrl = 'http://localhost:8080/signup';
  private loginUrl = 'http://localhost:8080/login';

  currentUserEmail: string | null = null;

  constructor(private http: HttpClient) { }

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

  setCurrentUserEmail(email: string): void {
    this.currentUserEmail = email;
  }

  getCurrentUserEmail(): string | null {
    return this.currentUserEmail;
  }

  getUserInfo(email: string): Observable<any> {
    const payload = { email: email };
    console.log('Sending getUserInfo request with payload:', payload);
    return this.http.post('http://localhost:8080/getUserInfo', payload)
      .pipe(
        catchError((error: HttpErrorResponse) => {
          console.error('Error fetching user info:', error);
          return throwError(error);
        })
      );
  }
  
  
}

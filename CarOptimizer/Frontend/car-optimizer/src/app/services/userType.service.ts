import { Injectable } from '@angular/core';
import { BehaviorSubject } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class UserType {

    private accountTypeSource = new BehaviorSubject<string>('User');
    currentAccountType = this.accountTypeSource.asObservable();
  
    constructor() { }
  
    changeAccountType(type: string) {
      this.accountTypeSource.next(type);
    }
  
    getAccountType(): string {
      return this.accountTypeSource.value;
    }
  }
